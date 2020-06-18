/**
  *****************************************************************************
  * @file    : message_app.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : message function
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
#include "queue.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef enum{
    MSG_ID_CNT,
    MSG_ID_TIME,
}MSG_ID_DEF;

typedef struct
{
    /* data */
    MSG_ID_DEF id;
    uint8_t data[128];
}MSG_DEF;

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_msg_send_cnt = NULL;
static TaskHandle_t task_msg_send_time = NULL;
static TaskHandle_t task_msg_rcv = NULL;

static QueueHandle_t queue_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static int msg_post_data(MSG_ID_DEF id, uint8_t *data, uint32_t len)
{
    BaseType_t xReturn = pdTRUE;

    MSG_DEF *msg = pvPortMalloc(sizeof(MSG_DEF));
    if (NULL == msg){
        return -1;
    }

    memset(msg, 0, sizeof(MSG_DEF));
    msg->id = id;
    memcpy(msg->data, data, len);

    xReturn = xQueueSend(queue_demo, &msg, 0);
    if (pdTRUE == xReturn){
        log_i("send message succeed");
    }else{
        log_i("send message error");
    }

    return 0;
}

/**
  * @brief  task_msg_send_cnt_task
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_send_cnt_task(void *p)
{
    log_d("%s", __FUNCTION__);
    uint8_t msg_cnt = 0;
    uint8_t buf[32] = {0};

    while(1){
        log_i("start send cnt message");

        memset(buf, 0, 32);
        snprintf(buf, 32, "this is send msg_cnt:%d", msg_cnt++);

        msg_post_data(MSG_ID_CNT, buf, strlen(buf));

        vTaskDelay(2500);
    }
}

/**
  * @brief  task_msg_send_cnt_task
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_send_time_task(void *p)
{
    log_d("%s", __FUNCTION__);
    uint8_t buf[32] = {0};

    while(1){
        log_i("start send time message");

        memset(buf, 0, 32);
        snprintf(buf, 32, "this time is:%d", xTaskGetTickCount());

        msg_post_data(MSG_ID_TIME, buf, strlen(buf));

        vTaskDelay(4000);
    }
}

/**
  * @brief  task_msg_rcv_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_rcv_cb(void *p)
{
    log_d("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    MSG_DEF *msg = NULL;

    while(1){
        // log_i("wait message");

        xReturn = xQueueReceive(queue_demo, &msg, portMAX_DELAY);
        if (pdTRUE != xReturn){
            log_e("recv message error\r\n");
            continue;
        }

        if (msg == NULL){
            continue;
        }

        switch(msg->id){
            case MSG_ID_CNT:
                log_i("recv cnt message:[%s]\r\n", msg->data);
                break;
            case MSG_ID_TIME:
                log_i("recv time message:[%s]\r\n", msg->data);
                break;
            default:
                break;
        }

        if (msg){
            vPortFree(msg);
            msg = NULL;
        }
    }
}

/**
  * @brief  message_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
BaseType_t message_init(void)
{
    BaseType_t xReturn = pdPASS;

    log_d("app task creat");

    #define MSG_LEN     5
    #define MSG_SIZE    (sizeof(MSG_DEF*))
    queue_demo = xQueueCreate(  (UBaseType_t ) MSG_LEN,
                                (UBaseType_t ) MSG_SIZE);
    if (NULL == queue_demo){
        return pdFAIL;
    }

    /* message task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_rcv_cb,
                            (const char *   )"task_msg_rcv",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_1ST,
                            (TaskHandle_t * )&task_msg_rcv);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    /* message task 队列发送任务1 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_send_cnt_task,
                            (const char *   )"task_msg_send_cnt",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_1ST,
                            (TaskHandle_t * )&task_msg_send_cnt);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    /* message task 队列发送任务2 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_send_time_task,
                            (const char *   )"task_msg_send_time",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&task_msg_send_time);

    if (pdPASS != xReturn){
        return pdFAIL;
    }

    return pdPASS;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/

