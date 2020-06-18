/**
  *****************************************************************************
  * @file    : timer_app.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : timer function
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-04-01
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "timers.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TimerHandle_t timer_1 = NULL;
static TimerHandle_t timer_2 = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void timer2_cb(void *p)
{
    log_i("timer 2 run just once\r\n");
}

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void timer1_cb(void *p)
{
    static uint32_t timer_cnt = 0;

    timer_cnt++;

    log_i("timer 1 run times:%d", timer_cnt);
    log_i("system tick:%d\r\n", xTaskGetTickCount());
}

/**
  * @brief  timer_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
BaseType_t timer_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_d("app task creat");

    timer_1 = xTimerCreate((const char *)"timer_1",
                            (TickType_t)2000,
                            (UBaseType_t)pdTRUE,
                            (void *)1,
                            (TimerCallbackFunction_t)timer1_cb);

    if (timer_1 == NULL){
        return pdFAIL;
    }

    xTimerStart(timer_1, 0);

    timer_2 = xTimerCreate((const char *)"timer_2",
                            (TickType_t)5000,
                            (UBaseType_t)pdFALSE,
                            (void *)2,
                            (TimerCallbackFunction_t)timer2_cb);

    if (timer_2 == NULL){
        return pdFAIL;
    }

    xTimerStart(timer_2, 0);

    return pdPASS;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/

