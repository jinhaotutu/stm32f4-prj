/**
  *****************************************************************************
  * @file    : http_client.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-12-29
  * @brief   : http app of http client
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-11-29
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is stm32 http client
  *****************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lwip_init.h"
#include "http_api.h"

/* Private define ------------------------------------------------------------*/
#define HTTP_DATA_BUF        1024

// 测试接口
#define POST_URL "http://www.kuaidi100.com/query"

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t http_client = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @note   http_client_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
static void http_client_cb(void *p)
{
    log_d("%s", __FUNCTION__);

    char recv_buf[HTTP_DATA_BUF]= {0};

    while (1){
        if (get_net_status() != NET_STATUS_GOT_IP){
            vTaskDelay(100);
            continue;
        }

        int recv_len = http_post_syn(POST_URL, NULL, NULL, recv_buf, HTTP_DATA_BUF);
        if (recv_len > 0){
            log_d("recv: %d\n%.*s", recv_len, recv_len, recv_buf);
        }else{
            log_e("post err");
        }

        vTaskDelay(10000);
    }
}

/**
  * @note   app_netconn_start
  * @brief  None
  * @param  None
  * @retval int
  */
int http_client_start(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate(  (TaskFunction_t )http_client_cb,
                            (const char *   )"http_client",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&http_client);

    if (pdPASS != xReturn){
        return pdFALSE;
    }

    return pdPASS;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
