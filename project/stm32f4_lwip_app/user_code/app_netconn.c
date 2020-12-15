/**
  *****************************************************************************
  * @file    : app_netconn.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : netconn with tcp and udp
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-11-29
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is stm32 netconn with tcp and udp
  *****************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip_init.h"

/* Private define ------------------------------------------------------------*/
#define SOCKET_DATA_SIZE        1024

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t tcp_server = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static void wait_net_config(void)
{
    while(get_net_status() != NET_STATUS_GOT_IP){
        vTaskDelay(100);
    }
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
static void tcp_server_cb(void *p)
{
    log_d("%s", __FUNCTION__);

    wait_net_config();

    int ret = 0;

    while (1){
        struct netconn *conn = netconn_new(NETCONN_TCP);
        if (NULL == conn){
            log_e("creat netconn err");
            vTaskDelay(5000);
            continue;
        }

        ret = netconn_bind(conn, IP_ADDR_ANY, 5555);
        if (ret < 0){
            log_e("bind netconn err");
            netconn_close(conn);
            netconn_delete(conn);
            continue;
        }

        ret = netconn_listen(conn);
        if (ret < 0){
            log_e("listen netconn err");
            netconn_close(conn);
            netconn_delete(conn);
            continue;
        }

        conn->recv_timeout = 3000;

        log_d("netconn tcp server is start");

        while(1){
            struct netconn *clientconn = NULL;
            ret = netconn_accept(conn, &clientconn);
            if (ret < 0){
                continue;
            }

            ip_addr_t ipaddr;
            u16_t port;
            netconn_getaddr(clientconn, &ipaddr, &port, 0);

            log_d("client ip:%s, port:%d", inet_ntoa(ipaddr), port);

            struct netbuf *recvbuf;
            int data_len = 0;
            char *recv_data = pvPortMalloc(SOCKET_DATA_SIZE);
            if (NULL == recv_data){
                netconn_close(clientconn);
                netconn_delete(clientconn);
                continue;
            }

            while(1){
                ret = netconn_recv(clientconn, &recvbuf);
                if (ret < 0){
                    if (ret == ERR_CLSD){
                        log_d("client closed");
                    }else{
                        log_d("recv err:%d", ret);
                    }
                    break;
                }else{
                    memset(recv_data, 0, SOCKET_DATA_SIZE);

                    for(struct pbuf *q=recvbuf->p;q!=NULL;q=q->next){
                        if(q->len > (SOCKET_DATA_SIZE-data_len)){
                            memcpy(recv_data+data_len, q->payload, (SOCKET_DATA_SIZE-data_len));
                        }else{
                            memcpy(recv_data+data_len,q->payload,q->len);
                        }

                        data_len += q->len;
                        if(data_len > SOCKET_DATA_SIZE){
                            break;
                        }
                    }

                    netbuf_delete(recvbuf);

                    log_d("netconn recv data:%s", recv_data);

                    ret = netconn_write(clientconn, recv_data, data_len, NETCONN_COPY);
                    if (ret < 0){
                        log_e("send err:%d", ret);
                    }

                    log_d("server send succees");

                    data_len = 0;
                }
            }

            vPortFree(recv_data);
            netconn_close(clientconn);
            netconn_delete(clientconn);
        }

        netconn_close(conn);
        netconn_delete(conn);
        vTaskDelay(1000);
    }
}

/**
  * @note   app_netconn_start
  * @brief  None
  * @param  None
  * @retval int
  */
int app_netconn_start(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate(  (TaskFunction_t )tcp_server_cb,
                            (const char *   )"tcp_server_netconn",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&tcp_server);

    if (pdPASS != xReturn){
        return pdFALSE;
    }

    return pdPASS;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
