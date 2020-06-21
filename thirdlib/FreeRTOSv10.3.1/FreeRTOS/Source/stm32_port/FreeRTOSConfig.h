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

