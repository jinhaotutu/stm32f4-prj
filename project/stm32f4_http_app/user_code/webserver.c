/**
  *****************************************************************************
  * @file    : app_socket.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : socket with tcp and udp
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-11-29
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is stm32 socket with tcp and udp
  *****************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lwip_init.h"
#include "http_webserver.h"

/* Private define ------------------------------------------------------------*/
#define WEBSERVER_PORT  "5678"
#define WEBFILE_PATH    "./index.html"

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t web_server = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static int server_frame_prase(const char *user_data, int len, const rsp_type *rsp)
{
    log_d("frame:%.*s", len, user_data);

    char *buf = "hello world";

    rsp->send(rsp->nc, user_data, len);
    rsp->send(rsp->nc, buf, strlen(buf));

    return 0;
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
static void web_server_cb(void *p)
{
    log_d("%s", __FUNCTION__);

    while(1){
        int ret = http_webserver(WEBSERVER_PORT, WEBFILE_PATH, server_frame_prase);
        if (0 != ret){
            log_e("http webserver error");
        }

        vTaskDelay(30000);
    }
}


/**
  * @note   app_socket_start
  * @brief  None
  * @param  None
  * @retval int
  */
int webserver_start(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate(  (TaskFunction_t )web_server_cb,
                            (const char *   )"web_server",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&web_server);

    if (pdPASS != xReturn){
        return pdFALSE;
    }

    return pdPASS;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
