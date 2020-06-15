/**
  *****************************************************************************
  * @file    : stm_config.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 freertos config file
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-06-02
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"


/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/
static TaskHandle_t xTask_creat;

/* Functions ------------------------------------------------------------------*/
extern void user_main(void *p);

/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
static void creat_task(void *p)
{
    log_d("%s", __FUNCTION__);
    int cnt = 0;

    /* creat app task in this 在这里创建应用任务 */
    taskENTER_CRITICAL();

    user_main(NULL);

    taskEXIT_CRITICAL();
    /* creat app task in this 在这里创建应用任务 */

#if 1
    /* delay task 延时退出，并删除本任务 */
    while(1){
        log_d("this is creat task:idle-%d", cnt++);
        vTaskDelay(1000);

        if (cnt >= 10){
            break;
        }
    }
#endif

    log_d("delete creat task");

    vTaskDelete(xTask_creat);
}

/**
  * @note   This function is used to creat app task and delect self.
  * @brief  None
  * @param  *p
  * @retval None
  */
int rtos_init(void)
{
    /* stm32 NVIC config */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    BaseType_t xReturn = pdPASS;

    log_i("Freertos v10.3.1 start ");

    /* first creat task in this 创建rtos第一个任务，用于创建其他任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )creat_task,
                            (const char *   )"creat_task",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_5ST,
                            (TaskHandle_t * )&xTask_creat);

    if (pdPASS != xReturn){
        return -1;
    }

    /* start task 开启任务调度 */
    vTaskStartScheduler();

    return xReturn;
}

/* systick */
#if 1
void SysTick_Handler(void)
{
    extern void xPortSysTickHandler( void );
    /* USER CODE END SysTick_IRQn 0 */
    #if (INCLUDE_xTaskGetSchedulerState == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
    #endif /* INCLUDE_xTaskGetSchedulerState */
        xPortSysTickHandler();
    #if (INCLUDE_xTaskGetSchedulerState == 1 )
    }
    #endif /* INCLUDE_xTaskGetSchedulerState */
}
#endif


/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

