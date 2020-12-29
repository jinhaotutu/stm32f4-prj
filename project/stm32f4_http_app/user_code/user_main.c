/**
  *****************************************************************************
  * @file    : user_main.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 user app code start
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-06-02
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is stm32 sockets app
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "config.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"

#include "eth_init.h"

/* Defines --------------------------------------------------------------------*/

/* Variables ------------------------------------------------------------------*/
static TaskHandle_t led_handle;
static TaskHandle_t network_handle;

/* Functions ------------------------------------------------------------------*/

/**
  * @note   led task
  * @brief  None
  * @param  *p
  * @retval None
  */
static void led_task(void *p)
{
    log_d("%s", __FUNCTION__);

    led_driver_init();
    uint8_t flag = 0;

    while(1){
        flag = !flag;
        led_driver_write(&flag, 1);
        log_d("led status is %s", flag?"on":"off");
        vTaskDelay(10000);

        log_i("free head size:%d", xPortGetFreeHeapSize());
        log_i("min head size:%d", xPortGetMinimumEverFreeHeapSize());

        log_i("net status:%d", get_net_status());
    }
}

/**
  * @note   This function is used to creat led task
  * @brief  None
  * @param  *p
  * @retval None
  */
int led_task_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_i("led task init");

    /* creat led task */
    xReturn = xTaskCreate(  (TaskFunction_t )led_task,
                            (const char *   )"led_task",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_HIGHEST,
                            (TaskHandle_t * )&led_handle);

    if (pdPASS != xReturn){
        return -1;
    }

    return xReturn;
}

/**
  * @note   user_main
  * @brief  None
  * @param  None
  * @retval None
  */
void user_main(void *p)
{
    log_d("user_main into");

    NetWork_Init();

    BaseType_t xReturn = pdPASS;

    xReturn = led_task_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }

    int http_client_start(void);
    xReturn = http_client_start();
    if (pdTRUE != xReturn){
        log_e("http_client_start err");
        return;
    }

    int webserver_start(void);
    xReturn = webserver_start();
    if (pdTRUE != xReturn){
        log_e("webserver_start err");
        return;
    }

    log_d("user_main exit");
}



/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

