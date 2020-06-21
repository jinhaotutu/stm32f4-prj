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

    /* creat app task in this 在这里创建应用任务 */
    taskENTER_CRITICAL();

    user_main(NULL);

    taskEXIT_CRITICAL();
    /* creat app task in this 在这里创建应用任务 */

#if 0
    int cnt = 0;

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
                            (UBaseType_t    )1,
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

#if (defined OS_DEBUG) && (OS_DEBUG == 1)

#if (defined configGENERATE_RUN_TIME_STATS) && (configGENERATE_RUN_TIME_STATS == 1)
#define USE_IRQ_TICK_CNT    0
#if USE_IRQ_TICK_CNT
static uint32_t rtos_run_time_cnt = 0;

/**
  * @note   TIM2_IRQHandler
  * @brief  None
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
        rtos_run_time_cnt++;

        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
#endif

/**
  * @note   rtos_sys_timer_init
  * @brief  None
  * @param  None
  * @retval None
  */
void rtos_sys_timer_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

#if !USE_IRQ_TICK_CNT
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = 16800-1;
    TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
#else
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = 168-1;
    TIM_TimeBaseStructure.TIM_Period = 100;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    rtos_run_time_cnt = 0;
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
#endif

    TIM_Cmd(TIM2, ENABLE);
}

/**
  * @note   rtos_sys_cnt_get
  * @brief  None
  * @param  None
  * @retval None
  */
uint32_t rtos_sys_cnt_get(void)
{
#if USE_IRQ_TICK_CNT
    return rtos_run_time_cnt;
#else
    return TIM_GetCounter(TIM2);
#endif
}
#endif

#endif

/* config function */
#ifdef OS_HOOK

#if (defined configUSE_IDLE_HOOK) && (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook( void )
{
    //log_d("%s", __FUNCTION__);
}
#endif

#if (defined configUSE_TICK_HOOK) && (configUSE_TICK_HOOK == 1)
void vApplicationTickHook( void )
{
    //printf("%s\r\n", __FUNCTION__);
}
#endif

#if (defined configUSE_MALLOC_FAILED_HOOK) && (configUSE_MALLOC_FAILED_HOOK == 1)
void vApplicationMallocFailedHook( void )
{
    log_d("%s", __FUNCTION__);
    log_e("os malloc fail");
}
#endif

#if (defined configCHECK_FOR_STACK_OVERFLOW) && (configCHECK_FOR_STACK_OVERFLOW >= 1)
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    log_d("%s", __FUNCTION__);
    log_e("task Overflow : %s [%p]", pcTaskName, xTask);
}
#endif

#if (defined configSUPPORT_STATIC_ALLOCATION) && (configSUPPORT_STATIC_ALLOCATION == 1)
/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif

#endif


/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

