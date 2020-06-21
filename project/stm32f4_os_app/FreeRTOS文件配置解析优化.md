# FreeRTOSConfig.h 配置优化及深入

---

**本篇目标：基于[上一篇的移植freertos(stm32f4_freertos)]()上，修改 FreeRTOSConfig.h 文件的相关配置来优化辅助 FreeRtos 的使用，并且建立一些基本功能（信号量、消息地列等）的简单应用位于(stm32f4_os_app)工程。**

资料准备：

- 最后工程：[项目工程(github分支)]() project 文件夹下的 stm32f4_os_app 工程。

---

## 配置优化简介

之前的移植功能只是将从源文件 demo中拷贝了一份 FreeRTOSConfig.h 做了一些移植修改而已，但是对于文件每个宏的定义，以及配置的修改没有做过多的深入。

所以这篇中的工程将 FreeRTOSConfig.h 进行了配置的修改与优化，并且注释了常用的宏定义的用途，详细的也会在下面进行解析，初步来看下相关的配置。

首先将 FreeRTOSConfig.h 的配置分成几部分：

- FreeRTOS 与系统有关的配置
- FreeRTOS 与功能api相关的配置
- FreeRTOS 相关钩子函数的配置
- FreeRTOS DEBUG调试相关的配置
- FreeRTOS 与系统优先级相关的配置
- FreeRTOS 应用自定义配置

---

## 配置优化解析

- FreeRTOS 与系统有关的配置：

  ```c
  /* RTOS CONFIG(配置) */
  
  /* 系统调度器配置 ：抢占式调度为1，时间片调度为0 */
  #define configUSE_PREEMPTION            1
  
  /* 移植系统(stm32)配置的时钟主频，stm32主频最高为 168MHz */
  #define configCPU_CLOCK_HZ              ( SystemCoreClock )
  
  /* Freertos 每 1/1000 s产生一次systick，来维持实时性调度 */
  #define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
  
  /* Freertos 配置的最大优先级，配置32以内的值 */
  #define configMAX_PRIORITIES            ( 10 )
  
  /* 空闲任务栈大小 */
  #define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 130 )
  
  /* 整个 Freertos 内存堆的大小 */
  #define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 75 * 1024 ) )
  
  /* 任务名称最大长度 */
  #define configMAX_TASK_NAME_LEN         ( 10 )
  
  /* 系统数据类型长度定义，stm32为32位，16位机开启该宏 */
  #define configUSE_16_BIT_TICKS          0
  
  /* 调度与空闲任务优先级相同的任务 */
  #define configIDLE_SHOULD_YIELD         0
  ```

- FreeRTOS 与功能api相关的配置：

  ```c
  /* RTOS API(资源使能与裁剪) */
  
  /* 与互斥锁相关 */
  #define configUSE_MUTEXES               1       //使能互斥锁
  #define configUSE_RECURSIVE_MUTEXES     1       //使能递归互斥锁
  #define configUSE_TASK_NOTIFICATIONS    1       //使能任务间通知
  #define configUSE_COUNTING_SEMAPHORES   1       //使能计数信号量
  #define configUSE_QUEUE_SETS            1       //使能消息集
  #define configQUEUE_REGISTRY_SIZE       8       //设置队列注册的个数
  
  #define configUSE_TIMERS                1       //使能定时器
  #if configUSE_TIMERS
      #define configTIMER_TASK_PRIORITY           ( 2 )
      #define configTIMER_QUEUE_LENGTH            10
      #define configTIMER_TASK_STACK_DEPTH        ( configMINIMAL_STACK_SIZE * 2 )
      #define configUSE_DAEMON_TASK_STARTUP_HOOK  0
  #endif
  
  /* Set the following definitions to 1 to include the API function, or zero
  to exclude the API function. (使能任务相关api) */
  #define INCLUDE_vTaskPrioritySet        1
  #define INCLUDE_uxTaskPriorityGet       1
  #define INCLUDE_vTaskDelete             1
  #define INCLUDE_vTaskCleanUpResources   0
  #define INCLUDE_vTaskSuspend            1
  #define INCLUDE_vTaskDelayUntil         1
  #define INCLUDE_vTaskDelay              1
  
  #define INCLUDE_xTaskGetIdleTaskHandle          0
  #define INCLUDE_xTaskGetCurrentTaskHandle       1
  #define INCLUDE_uxTaskGetStackHighWaterMark     1
  #define INCLUDE_xTaskGetSchedulerState          1
  ```

- FreeRTOS 相关钩子函数的配置，需要定义钩子函数，钩子函数定义放在了工程 stm_config.c 中：

  ```c
  #define configUSE_IDLE_HOOK             1
  /* 空闲任务钩子函数使能，需要定义下列函数，此函数在空闲函数 prvIdleTask 中调用 */
  void vApplicationIdleHook( void )
  {
      //log_d("%s", __FUNCTION__);
  }
  
  /* 空闲任务低功耗函数使能，stm32 已经在 port.c 中定义了 vPortSuppressTicksAndSleep 函数，在空闲函数 prvIdleTask 中调用 */
  #define configUSE_TICKLESS_IDLE         0       //
  
  
  #define configUSE_TICK_HOOK             0
  /* tick钩子函数使能，需要定义下列函数，此函数在systick中断函数中由 xTaskIncrementTick 调用 */
  void vApplicationTickHook( void )
  {
      //printf("%s\r\n", __FUNCTION__);
  }
  
  
  #define configUSE_MALLOC_FAILED_HOOK    1
  /* 内存申请失败钩子函数使能，需要定义下列函数，此函数在内存申请函数pvPortMalloc中调用 */
  void vApplicationMallocFailedHook( void )
  {
      log_d("%s", __FUNCTION__);
      log_e("os malloc fail");
  }
  
  
  #define configCHECK_FOR_STACK_OVERFLOW  2
  /* 任务栈溢出检测钩子函数使能，需要定义下列函数，此函数在PendSV函数中由 vTaskSwitchContext调用。
   * 任务堆栈检测有两种方式，发生异常则会调用钩子函数：
   * 方式1为检查当前任务栈指针是否在任务栈的合法空间内。
   * 方式2为在任务栈最后区域填入0xa5a5a5a5的数据，每次调度的时候检查数据是否有改动。
   */
  void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
  {
      log_d("%s", __FUNCTION__);
      log_e("task Overflow : %s [%p]", pcTaskName, xTask);
  }
  
  
  #define configSUPPORT_STATIC_ALLOCATION 0
  /* 静态任务创建函数使能，需要定义下列官方示例函数，使能后可以使用 xTaskCreateStatic 函数 */
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
  ```

- FreeRTOS DEBUG调试相关的配置，函数实现在工程 stm_config.c 中：

  ```c
  /* 使能以下两个宏，既可以使用任务可视化追踪，可以调用 vTaskList 打印任务信息 */
  #define configUSE_TRACE_FACILITY                1
  #define configUSE_STATS_FORMATTING_FUNCTIONS    1
  
  /* 使能下面的宏，将可以调用 vTaskGetRunTimeStats 查看任务占用情况
   * rtos_sys_timer_init 为定时器初始化，定义一个10倍tick(100Hz)以上的速率来计算任务占用率
   * rtos_sys_cnt_get 为获取按上述速率增加的计数值
   */
  #define configGENERATE_RUN_TIME_STATS   1
  #if (defined configGENERATE_RUN_TIME_STATS) && (configGENERATE_RUN_TIME_STATS == 1)
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()  rtos_sys_timer_init()
  #define portGET_RUN_TIME_COUNTER_VALUE()          rtos_sys_cnt_get()
  #endif
  
  /* Normal assert() semantics without relying on the provision of an assert.h
      header file. (断言) */
  #include "elog.h"
  #define OS_ASSERT(x)       log_e(x)
  #define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); OS_ASSERT("os err"); for( ;; ); }
  ```

- FreeRTOS 与系统优先级相关的配置：

  ```c
  
  ```

- FreeRTOS 应用自定义配置：

  ```c
  /* 定义常用的优先级，进行应用应用，避免应用编程出现直接的数值 */
  #define RTOS_PRIORITY_HIGHEST       (configMAX_PRIORITIES-1)
  #define RTOS_PRIORITY_LEVEL_1ST     (configMAX_PRIORITIES-2)
  #define RTOS_PRIORITY_LEVEL_2ST     (configMAX_PRIORITIES-3)
  #define RTOS_PRIORITY_LEVEL_3ST     (configMAX_PRIORITIES-4)
  #define RTOS_PRIORITY_LEVEL_4ST     (configMAX_PRIORITIES-5)
  #define RTOS_PRIORITY_LEVEL_5ST     (configMAX_PRIORITIES-6)
  ```



也贴一下修改后所有的 FreeRTOSConfig.h 以及移植适配的 stm_config.c 文件：

```c
/*
 * FreeRTOS Kernel V10.3.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined (__ICCARM__) || defined (__CC_ARM) || defined (__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

#ifndef USE_OS
#define USE_OS
#endif

/* RTOS CONFIG(配置) */
#define configUSE_PREEMPTION            1       //抢占式调度：1 | 时间片调度：0
#define configCPU_CLOCK_HZ              ( SystemCoreClock )          //移植系统运行主频
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )      //RTOS运行tick时钟
#define configMAX_PRIORITIES            ( 10 )                       //RTOS最大优先级
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 130 )   //RTOS任务最小栈大小
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 75 * 1024 ) ) //RTOS内存堆大小
#define configMAX_TASK_NAME_LEN         ( 10 )                       //任务名称最大长度
#define configUSE_16_BIT_TICKS          0       //数据类型长度定义，32位为0，16位或8位开启
#define configIDLE_SHOULD_YIELD         0       //使能与空闲任务优先级相同的任务


/* RTOS API(资源使能与裁剪) */
#define configUSE_MUTEXES               1       //使能互斥锁
#define configUSE_RECURSIVE_MUTEXES     1       //使能递归互斥锁
#define configUSE_TASK_NOTIFICATIONS    1       //使能任务间通知
#define configUSE_COUNTING_SEMAPHORES   1       //使能计数信号量
#define configUSE_QUEUE_SETS            1       //使能队列集
#define configQUEUE_REGISTRY_SIZE       8       //设置队列注册的个数

#define configUSE_TIMERS                1       //使能定时器
#if configUSE_TIMERS
    #define configTIMER_TASK_PRIORITY           ( 2 )
    #define configTIMER_QUEUE_LENGTH            10
    #define configTIMER_TASK_STACK_DEPTH        ( configMINIMAL_STACK_SIZE * 2 )
    #define configUSE_DAEMON_TASK_STARTUP_HOOK  0
#endif

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. (使能任务相关api) */
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskCleanUpResources   0
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskDelay              1

#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetSchedulerState          1


/* RTOS HOOK(功能钩子函数) */
#ifdef OS_HOOK
    #define configUSE_IDLE_HOOK             1       //空闲任务钩子函数
    #define configUSE_TICKLESS_IDLE         0       //空闲任务低功耗功能使能
    #define configUSE_TICK_HOOK             0       //tick时钟钩子函数
    #define configUSE_MALLOC_FAILED_HOOK    1       //内存申请失败的钩子函数
    #define configCHECK_FOR_STACK_OVERFLOW  2       //任务栈溢出检测
    #define configSUPPORT_STATIC_ALLOCATION 0       //额外静态任务创建，需添加额外函数
#else
    #define configUSE_IDLE_HOOK             0       //空闲函数钩子函数
    #define configUSE_TICK_HOOK             0       //tick时钟钩子函数
#endif


/* RTOS TASK DEBUG(任务资源调试) */
#if (defined OS_DEBUG) && (OS_DEBUG == 1)
    #define configUSE_TRACE_FACILITY                1       //使能任务可视化追踪
    #define configUSE_STATS_FORMATTING_FUNCTIONS    1

    #define configGENERATE_RUN_TIME_STATS   1               //使能任务状态统计函数-计算任务占用率
    #if (defined configGENERATE_RUN_TIME_STATS) && (configGENERATE_RUN_TIME_STATS == 1)
        #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()  rtos_sys_timer_init()
        #define portGET_RUN_TIME_COUNTER_VALUE()          rtos_sys_cnt_get()
    #endif

    /* Normal assert() semantics without relying on the provision of an assert.h
    header file. (断言) */
    #include "elog.h"
    #define OS_ASSERT(x)       log_e(x)
    #define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); OS_ASSERT("os err"); for( ;; ); }
#endif

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                        0
#define configMAX_CO_ROUTINE_PRIORITIES              ( 2 )

/* Cortex-M specific definitions. (stm32与os相关中断优先级的配置) */
#ifdef __NVIC_PRIO_BITS
    /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
    #define configPRIO_BITS             __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS             4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
// #define xPortSysTickHandler SysTick_Handler


/* others */


/* user config code (用户自定义配置) */
#if (configMAX_PRIORITIES > 6)
    #define RTOS_PRIORITY_HIGHEST       (configMAX_PRIORITIES-1)
    #define RTOS_PRIORITY_LEVEL_1ST     (configMAX_PRIORITIES-2)
    #define RTOS_PRIORITY_LEVEL_2ST     (configMAX_PRIORITIES-3)
    #define RTOS_PRIORITY_LEVEL_3ST     (configMAX_PRIORITIES-4)
    #define RTOS_PRIORITY_LEVEL_4ST     (configMAX_PRIORITIES-5)
    #define RTOS_PRIORITY_LEVEL_5ST     (configMAX_PRIORITIES-6)
#endif


#endif /* FREERTOS_CONFIG_H */


```

```c
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


```

---

## 功能简单应用

在 stm32f4_os_app 工程中，建立了有关任务、信号量、消息队列、互斥锁、定时器、事件通知的简单应用。工程及运行情况如下：

![image-20200621234419100](C:\Users\jinhao\AppData\Roaming\Typora\typora-user-images\image-20200621234419100.png)

![image-20200621235149271](C:\Users\jinhao\AppData\Roaming\Typora\typora-user-images\image-20200621235149271.png)

---

### 小结

