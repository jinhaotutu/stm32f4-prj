/**
  *****************************************************************************
  * @file    : http_api.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-12-29
  * @brief   : mongoose http post api
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

/* Defines --------------------------------------------------------------------*/
#define SHOW_HEADER_LOG     0


/* Variables ------------------------------------------------------------------*/
typedef struct post_info
{
    /* data */
    char *recv_data;
    unsigned int recv_len;
    unsigned char poll;
    void *user_data;
}post_info;

/* Functions ------------------------------------------------------------------*/

/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
static void ev_handler(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;

    post_info *info = (post_info *)nc->user_data;

    switch (ev) {
        case MG_EV_CONNECT:
            if (*(int *) ev_data != 0) {
                fprintf(stderr, "connect() failed: %s\n", strerror(*(int *) ev_data));
                info->poll = false;
            }
#if SHOW_HEADER_LOG
            printf("connect() success\n");
#endif
            break;
        case MG_EV_HTTP_REPLY:
            nc->flags |= MG_F_CLOSE_IMMEDIATELY;
#if SHOW_HEADER_LOG
            printf("response:\n%.*s\n", hm->message.len, hm->message.p);
#endif

            if (NULL != info->recv_data){
                if (info->recv_len >= hm->body.len){
                    memcpy(info->recv_data, hm->body.p, hm->body.len);
                }else{
                    memcpy(info->recv_data, hm->body.p, info->recv_len);
                }
                info->recv_len = hm->body.len;
            }else{
                info->recv_len = 0;
            }

            info->poll = false;
            break;
        case MG_EV_CLOSE:
#if SHOW_HEADER_LOG
            printf("closed connection\n");
#endif
            info->poll = false;
            break;
        default:
            break;
    }
}

int http_post_syn(const char *url, const char *post_data, char *body_buf, int body_len)
{
    if (NULL == url){
        return -1;
    }

    struct mg_mgr mgr={0};

    mg_mgr_init(&mgr, NULL);
    // mg_set_nameserver(&mgr, "114.114.114.114");

    struct mg_connection *nc = mg_connect_http(&mgr, ev_handler, url, NULL, post_data);
    if(NULL == nc){
        return -1;
    }

#if SHOW_HEADER_LOG
    printf("request:\n%.*s\n", nc->send_mbuf.len, nc->send_mbuf.buf);
#endif

    post_info info = {0};
    info.poll = true;
    info.recv_data = body_buf;
    info.recv_len = body_len;
    nc->user_data = (void *)&info;

    while (info.poll) {
        mg_mgr_poll(&mgr, 100);
    }
    mg_mgr_free(&mgr);

    return info.recv_len;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

