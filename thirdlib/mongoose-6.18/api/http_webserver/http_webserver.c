/**
  *****************************************************************************
  * @file    : http_webserver.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-12-29
  * @brief   : mongoose http webserver api
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-12-29
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "mongoose.h"
#include "http_webserver.h"

/* Defines --------------------------------------------------------------------*/
#define SHOW_HEADER_LOG     0

/* Variables ------------------------------------------------------------------*/
typedef struct server_info
{
    /* data */
    unsigned char poll;
    struct mg_serve_http_opts opts;
    server_user cb;
    rsp_type rsp;
    void *user_data;
}server_info;

/* Functions ------------------------------------------------------------------*/

/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
static void rsp_send(const void *nc, const void *data, size_t len)
{
#if SHOW_HEADER_LOG
    printf("frame send:%.*s\n", len, (char *)data);
#endif
    mg_send_websocket_frame((struct mg_connection *)nc, WEBSOCKET_OP_TEXT, data, len);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data)
{
    server_info *info = (server_info *)nc->user_data;

    switch (ev) {
        case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
#if SHOW_HEADER_LOG
            printf("++ joined:%d\n", nc->sock);
#endif
            break;
        }

        case MG_EV_WEBSOCKET_FRAME: {
            struct websocket_message *wm = (struct websocket_message *) ev_data;
            if (NULL != info->cb){
                info->rsp.nc = (void *)nc;
                info->cb(wm->data, wm->size, &(info->rsp));
            }

#if SHOW_HEADER_LOG
            printf("%d-message:\n%.*s\n", nc->sock, wm->size, wm->data);
#endif
            break;
        }

        case MG_EV_HTTP_REQUEST: {
            struct http_message *hm = (struct http_message *) ev_data;
#if SHOW_HEADER_LOG
            printf("request:\n%.*s\n", hm->message.len, hm->message.p);
#endif

            mg_serve_http(nc, (struct http_message *) ev_data, info->opts);

#if SHOW_HEADER_LOG
            printf("response:\n%.*s\n", nc->send_mbuf.len, nc->send_mbuf.buf);
#endif
            break;
        }

        case MG_EV_CLOSE: {
            if (nc->flags & MG_F_IS_WEBSOCKET){
#if SHOW_HEADER_LOG
                printf("-- left\n");
#endif
            }
            break;
        }

        default:
            break;
    }
}

int http_webserver(const char *port, const char *path, server_user cb)
{
    if (NULL == port || NULL == path){
        return -1;
    }

    struct mg_mgr mgr={0};

    mg_mgr_init(&mgr, NULL);

    struct mg_connection *nc = mg_bind(&mgr, port, ev_handler);
    if(NULL == nc){
        return -1;
    }

    server_info info = {0};
    info.poll = true;
    info.cb = cb;
    info.rsp.send = rsp_send;

    char root[32]={0};
    char file[16]={0};
    const char *p = path;
    while (1){
        char *q = strchr(p, '/');
        if (NULL == q){
            break;
        }

        p = q+1;
    }

    if (p == path){
        info.opts.document_root = ".";
        info.opts.index_files = path;
    }else{
        memcpy(root, path, (p-path));
        memcpy(file, p, strlen(p));

        info.opts.document_root = root;
        info.opts.index_files = file;
    }

    nc->user_data = (void *)&info;

    mg_set_protocol_http_websocket(nc);

    while (info.poll) {
        mg_mgr_poll(&mgr, 100);
    }
    mg_mgr_free(&mgr);

    return 0;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

