/**
  *****************************************************************************
  * @file    : mutex_app.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : mutex function
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
#include "semphr.h"

/* Private define ------------------------------------------------------------*/

/* 宏定义说明：利用两个线程对同一个变量进行自++操作，来模拟mutex的作用
 * 用延迟来模拟极端条件下的资源抢占，在不使能mutex可以发现变量的自++不在预期范围内，
 * 导致每个线程的取值可能不符合预期，程序可能会出现未知的情况；使能mutex后可以发现变量
 * 正常的递增++
 */
#define ENABLE_MUTEX    1

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_mutex_1 = NULL;
static TaskHandle_t task_mutex_2 = NULL;
static SemaphoreHandle_t mutex_demo = NULL;

static uint32_t mutex_cnt = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_sem_post_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_mutex_1_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    uint32_t cnt = 0;

    while(1){
#if ENABLE_MUTEX
        xSemaphoreTake(mutex_demo, portMAX_DELAY);
#endif

        mutex_cnt++;
        cnt = mutex_cnt;

        vTaskDelay(3000);

        log_i("mutex task1 printf in cnt:%d", mutex_cnt);
        mutex_cnt = cnt;
        // log_i("mutex task1 printf out cnt:%d\r\n", mutex_cnt);

#if ENABLE_MUTEX
        xSemaphoreGive(mutex_demo);
#endif

        vTaskDelay(1000);
    }
}

/**
  * @brief  task_sem_wait_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_mutex_2_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    uint32_t cnt = 0;

    while(1){
        vTaskDelay(1000);

#if ENABLE_MUTEX
        xSemaphoreTake(mutex_demo, portMAX_DELAY);
#endif

        mutex_cnt++;
        cnt = mutex_cnt;

        vTaskDelay(3000);

        log_i("mutex task2 printf in cnt:%d", mutex_cnt);
        mutex_cnt = cnt;
        // log_i("mutex task2 printf out cnt:%d\r\n", mutex_cnt);

#if ENABLE_MUTEX
        xSemaphoreGive(mutex_demo);
#endif
    }
}

/**
  * @brief  mutex_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
BaseType_t mutex_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_d("app task creat");

    mutex_demo = xSemaphoreCreateMutex();
    if (NULL == mutex_demo){
        return pdFAIL;
    }

    /* message task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_mutex_1_cb,
                            (const char *   )"task_mutex_1",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_mutex_1);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    /* message task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_mutex_2_cb,
                            (const char *   )"task_mutex_2",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_mutex_2);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    return pdTRUE;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/

