/**
  *****************************************************************************
  * @file    : event_app.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : event function
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
#include "event_groups.h"

/* Private define ------------------------------------------------------------*/
#define EVENT_1_BIT     (0x01 << 0)
#define EVENT_2_BIT     (0x01 << 7)

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_event_rev1 = NULL;
static TaskHandle_t task_event_rev2 = NULL;
static TaskHandle_t task_event_post = NULL;

static EventGroupHandle_t event_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_rev2_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    EventBits_t event_t;

    while(1){
        event_t = xEventGroupWaitBits(event_demo, EVENT_1_BIT | EVENT_2_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        if (event_t & EVENT_1_BIT){
            log_i("event recv2 num is event_1_bit:%02x", event_t);
        }else{
        }

        if (event_t & EVENT_2_BIT){
            log_i("event recv2 num is event_2_bit:%02x", event_t);
        }else{
        }

        printf("\r\n");
    }
}

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_rev1_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    EventBits_t event_t;

    while(1){
        event_t = xEventGroupWaitBits(event_demo, EVENT_1_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        if (event_t & EVENT_1_BIT){
            log_i("event recv1 num is event_1_bit:%02x\r\n", event_t);
        }else{
            log_i("not match");
        }
    }
}

/**
  * @brief  task_event_post_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_post_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        vTaskDelay(1000);

        xEventGroupSetBits(event_demo, EVENT_1_BIT);

        vTaskDelay(2000);

        xEventGroupSetBits(event_demo, EVENT_2_BIT);

        vTaskDelay(3000);

        xEventGroupSetBits(event_demo, EVENT_1_BIT | EVENT_2_BIT);
    }
}

/**
  * @brief  event_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
BaseType_t event_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_d("app task creat");

    event_demo = xEventGroupCreate();
    if (NULL == event_demo){
        return pdFAIL;
    }

    /* event task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_event_rev1_cb,
                            (const char *   )"task_event_rev1",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&task_event_rev1);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_event_rev2_cb,
                            (const char *   )"task_event_rev2",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&task_event_rev2);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    /* event task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_event_post_cb,
                            (const char *   )"task_event_post",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_1ST,
                            (TaskHandle_t * )&task_event_post);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    return pdPASS;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/
