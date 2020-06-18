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
  * this is stm32 with freertos app
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "config.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"

/* Defines --------------------------------------------------------------------*/
/* 在此设置 Freertos 的各个例程的开关 */
#define OS_TASK_LED         1
#define OS_TASK_CPU         1
#define OS_APP_SEM          0
#define OS_APP_MSG          0
#define OS_APP_MUTEX        0
#define OS_APP_TIMER        0
#define OS_APP_EVENT        0

/* Variables ------------------------------------------------------------------*/
static TaskHandle_t led_handle;

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
        vTaskDelay(1000);
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
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_4ST,
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

    BaseType_t xReturn = pdPASS;

#if OS_TASK_LED
    xReturn = led_task_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_TASK_CPU
    xReturn = cpu_task_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_APP_SEM
    xReturn = sem_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_APP_MSG
    xReturn = message_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_APP_MUTEX
    xReturn = mutex_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_APP_TIMER
    xReturn = timer_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

#if OS_APP_EVENT
    xReturn = event_init();
    if (pdTRUE != xReturn){
        log_e("init err");
        return;
    }
#endif

    log_d("user_main exit");
}



/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

