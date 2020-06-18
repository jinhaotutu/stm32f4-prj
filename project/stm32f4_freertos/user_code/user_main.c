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
  * this is stm32 with freertos
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "config.h"
#include "led.h"

#ifdef USE_OS
#include "FreeRTOS.h"
#include "task.h"
#endif

/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/
#ifdef USE_OS
static TaskHandle_t led_handle;
static TaskHandle_t cnt_handle;
#endif

/* Functions ------------------------------------------------------------------*/

#ifdef USE_OS
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
                            (UBaseType_t    )3,
                            (TaskHandle_t * )&led_handle);

    if (pdPASS != xReturn){
        return -1;
    }
		
		return xReturn;
}

/**
  * @note   led task
  * @brief  None
  * @param  *p
  * @retval None
  */
static void cnt_task(void *p)
{
    log_d("%s", __FUNCTION__);

    uint16_t cnt = 0;

    while(1){
        cnt++;
        log_d("every 5s , cnt times is %d", cnt);
        vTaskDelay(5000);
    }
}

/**
  * @note   This function is used to creat led task
  * @brief  None
  * @param  *p
  * @retval None
  */
int cnt_task_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_i("cnt task init");

    /* creat led task */
    xReturn = xTaskCreate(  (TaskFunction_t )cnt_task,
                            (const char *   )"cnt_task",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )2,
                            (TaskHandle_t * )&cnt_handle);

    if (pdPASS != xReturn){
        return -1;
    }
		
		return xReturn;
}
#endif

/**
  * @note   user_main
  * @brief  None
  * @param  None
  * @retval None
  */
void user_main(void *p)
{
    log_d("user_main into");

#ifdef USE_OS
    led_task_init();
	
    cnt_task_init();
#endif

    log_d("user_main exit");
}



/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

