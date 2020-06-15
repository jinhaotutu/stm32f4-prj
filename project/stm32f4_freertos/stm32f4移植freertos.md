# STM32F4基础工程移植FreeRTOS

---

**本篇目标：基于[上一篇的基础工程(stm32f4_first_demo)](https://blog.csdn.net/q361750389/article/details/106726799)上，移植freertos，建立移植工程(stm32f4_freertos)。**

资料准备：

- [Freertos源文件](https://www.freertos.org/a00104.html)
- 最后工程：[项目工程(github分支)](https://github.com/jinhaotutu/stm32f4-prj/tree/stm32_freertos) project 文件夹下的 stm32f4_freertos 工程。

---

## Freertos源文件目录说明

```c
.
├─FreeRTOS                          //只展示了会用到的子文件夹
│  ├─Demo
│  │  └─CORTEX_M4F_STM32F407ZG-SK   //应用示例，会用到文件夹下的FreeRTOSConfig.h文件
│  ├─License
│  └─Source                         //源代码文件夹
│      ├─include                    //头文件
│      └─portable                   //移植相关文件
│          ├─GCC
│          │  └─ARM_CM4F            //在stm32cubeide(gcc)环境下的stm32移植文件
│          ├─MemMang                //内存管理文件
│          └─RVDS
│              └─ARM_CM4F           //在keil环境下的stm32移植文件
└─FreeRTOS-Plus                     //其他freertos应用文件
```

ps：上述是freertos源文件目录，一些用不到的目录做了一些过滤，主要关注这几个目录文件就可以了：

- source 文件目录，目录下的 .c 文件为freertos的核心文件。
- ARM_CM4F 文件夹下是对应各种stm32的移植文件。
- MemMang 文件夹下是内存管理文件，一般场景都选择 heap_4，具体可以在后面分析的时候看。
- FreeRTOSConfig.h 用于配置 freertos ，可以在demo工程中copy一个然后结合自己的情况修改。

---

## Freertos源文件移植改动

这部分主要涉及的是 freertos 部分的改动。

1. 我们创建一个 stm32_port 文件夹专门来存放移植相关的配置文件，这样可以更好的模块化。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020061521151799.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70)
2. 复制 MemMang 文件夹到 stm32_port 下，实际用到的是 heap_4.c 文件。

3. keil环境复制 portable目录下的 RVDS 文件夹到 stm32_port 下；stm32cubeide复制 portable目录下的 GCC 文件夹到 stm32_port 下。

4. 复制 demo 工程中 CORTEX_M4F_STM32F407ZG-SK 文件夹下的 FreeRTOSConfig.h 到 stm32_port 下。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200615211612848.png)
以上是修改建立直观的移植目录，接下来就是代码修改，修改 FreeRTOSConfig.h 相关配置项：

```c
// 1. ------------------------------------------------------
//源--45行
#ifdef __ICCARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif
// 修改后：增加不同编译环境的配置
#if defined (__ICCARM__) || defined (__CC_ARM) || defined (__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

// 2. ------------------------------------------------------
// 源--51、52、64、66行，修改宏定义为0，暂时不需要使用到这些钩子函数
#define configUSE_IDLE_HOOK				0//1
#define configUSE_TICK_HOOK				0//1
#define configCHECK_FOR_STACK_OVERFLOW	0//2
#define configUSE_MALLOC_FAILED_HOOK	0//1

// 3. ------------------------------------------------------
// 源--124行，注释宏定义，该中断函数我们自己实现
//#define xPortSysTickHandler SysTick_Handler
```

上面是修改的内容，贴一份实际修改后的配置文件：

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

#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK				0
#define configUSE_TICK_HOOK				0
#define configCPU_CLOCK_HZ				( SystemCoreClock )
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES			( 5 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 130 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 75 * 1024 ) )
#define configMAX_TASK_NAME_LEN			( 10 )
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			1
#define configUSE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE		8
#define configCHECK_FOR_STACK_OVERFLOW	0
#define configUSE_RECURSIVE_MUTEXES		1
#define configUSE_MALLOC_FAILED_HOOK	0
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1
#define configGENERATE_RUN_TIME_STATS	0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
// #define xPortSysTickHandler SysTick_Handler


/* user config code 额外定义了常用优先级的宏定义 */
#define RTOS_PRIORITY_HIGHEST       (10)
#define RTOS_PRIORITY_LEVEL_1ST     (9)
#define RTOS_PRIORITY_LEVEL_2ST     (8)
#define RTOS_PRIORITY_LEVEL_3ST     (7)
#define RTOS_PRIORITY_LEVEL_4ST     (6)
#define RTOS_PRIORITY_LEVEL_5ST     (5)

#endif /* FREERTOS_CONFIG_H */


```

---

## stm32f4移植改动

这一部分为涉及到stm32的代码，主要就是我们自己实现的 SysTick_Handler 中断。

1. 在 stm32_port 文件夹下创建 stm_config.c ，用于涉及 stm32 部分的代码与初始化接口。

2. 实现 SysTick_Handler 中断函数：

   ```c
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
   ```

---

## 初始化Freertos并搭建应用任务

至上，移植工作已经做完了，但是需要把配置好的 freertos 用起来，所以少不了初始化与应用任务的建立。

1. 在 stm_config.c 实现以下内容：

   ```c
   #include "FreeRTOS.h"
   #include "task.h"
   
   static TaskHandle_t xTask_creat;
   
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
   
       //user_main(NULL);     //调用自己的应用函数接口
   
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
   ```

2. 在 main函数中调用封装好的初始化接口 rtos_init 即可。

   ```c
   //main函数调用示例
   int main(void)
   {
       /* stm32系统配置 */
       Sys_Config();
   
       extern int rtos_init(void);
       rtos_init();
   
       log_e("never get here");
   
       while(1)
       {
       }
   }
   ```

同样贴上 stm_config.c 的全部代码：

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
    /* stm32 NVIC config 必须配置成分组4 */
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


```

---

### 实际运行

上面基本的移植，初始化 freertos 的工作基本完成了，可以编译烧录运行看一下效果：（可以根据自己的环境打开 stm32f4_freertos 中的工程来运行看看）
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200615212627654.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200615212640659.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200615212655528.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70)

---

### 小结

做个小结，移植 freertos 涉及到的几个方面：

1. 与移植硬件相关的 portable 文件，有能力的同学可以自己编写，像stm32比较大众的有现有的文件，可以直接拿来使用，如上移植。
2. 内存管理默认情况下都使用 heap_4.c 文件，在特殊多内存管理的时候才会用到 heap_5.c等。
3. 修改 FreeRTOSConfig.h 的配置，将刚开始不必要的HOOK宏定义去除，只编译基本的功能。
4. 自己定义 SysTick_Handler 函数，方便后续拓展，以及完成初始化创建任务的代码。



ps：为什么要重新创建一个 stm_config.c 文件？因为将所有有关 freertos 移植的文件以及与硬件相关的代码都放在了 stm32_port 文件夹下，这样后续跨平台移植的时候，修改该文件夹下和硬件相关的内容即可，不需要大动工程与框架，保证后续应用移植开发的方便性。



想要不基于上面的基础工程，移植到自己的 stm32f4 工程当中，只需要将 thirdlib 文件夹下的 FreeRTOSv10.3.1 拷贝到自己的工程中，然后调用初始化 rtos_init 即可。

---

如有其它移植上面的问题自己问我哦~后续会对移植相关及freertos部分源码进行解析，深入理解才可以更好的运用。


<img src="https://img-blog.csdnimg.cn/20200507175326677.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3EzNjE3NTAzODk=,size_16,color_FFFFFF,t_70#pic_center" width=300 height=330> 

Tuu