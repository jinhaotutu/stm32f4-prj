/**
  *****************************************************************************
  * @file    : sem_app.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : sem function
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

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_sem_post = NULL;
static TaskHandle_t task_sem_wait = NULL;
static SemaphoreHandle_t sem_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_sem_post_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_sem_post_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        log_d("start post sem");

        xReturn = xSemaphoreGive(sem_demo);
        if (pdTRUE == xReturn){
            log_i("post sem succeed");
        }else{
            log_i("post sem error");
        }

        vTaskDelay(2500);
    }
}

/**
  * @brief  task_sem_wait_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_sem_wait_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        log_d("wait sem");
        xReturn = xSemaphoreTake(sem_demo, portMAX_DELAY);
        if (pdTRUE == xReturn){
            log_i("get sem succeed\r\n");
        }else{
            log_i("get sem error\r\n");
        }
    }
}

/**
  * @brief  sem_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
BaseType_t sem_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_d("sem task creat");

    sem_demo = xSemaphoreCreateBinary();
    if (NULL == sem_demo){
        return pdFAIL;
    }

    /* message task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_sem_post_cb,
                            (const char *   )"task_sem_post",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_1ST,
                            (TaskHandle_t * )&task_sem_post);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    /* message task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_sem_wait_cb,
                            (const char *   )"task_sem_wait",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&task_sem_wait);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    return pdPASS;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/

