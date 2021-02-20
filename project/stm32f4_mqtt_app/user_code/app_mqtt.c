/**
  *****************************************************************************
  * @file    : app_mqtt.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2021-01-03
  * @brief   : mqtt client demo
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2021-01-03
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is stm32 mqtt client demo
  *****************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lwip_init.h"
#include "mqtt_api.h"

/* Private define ------------------------------------------------------------*/
#define MQTT_URL    "localhost"
#define MQTT_PORT   1883

#define MQTT_SUBSCRIBE_TOPIC    "productid/deviceid/property/#"
#define MQTT_PUBLISH_TOPIC_1    "productid/deviceid/property/set"
#define MQTT_PUBLISH_TOPIC_2    "productid/deviceid/property/get"

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t mqtt_client = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static void wait_net_config(void)
{
    while(get_net_status() != NET_STATUS_GOT_IP){
        vTaskDelay(100);
    }
}

int mqtt_topic_parse(const char *topic, int topic_len, const char *data, int data_len)
{
    printf("topic:%.*s\n", topic_len, topic);
    printf("payload:%.*s\n", data_len, data);

    return 0;
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
static void mqtt_client_cb(void *p)
{
    log_d("%s", __FUNCTION__);

    wait_net_config();

    mqtt_client_connect(MQTT_URL, MQTT_PORT, "mqtt_id", "user", "password", mqtt_topic_parse);

    mqtt_subscribe(MQTT_SUBSCRIBE_TOPIC, 0);

    while(1)
    {
        mqtt_loop();

        vTaskDelay(5000);
        mqtt_publish(MQTT_PUBLISH_TOPIC_1, 0, "hello world", strlen("hello world"));
        mqtt_publish(MQTT_PUBLISH_TOPIC_2, 0, "see you", strlen("see you"));
    }

    mqtt_client_exit();
}

/**
  * @note   app_netconn_start
  * @brief  None
  * @param  None
  * @retval int
  */
int mqtt_client_start(void)
{
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate(  (TaskFunction_t )mqtt_client_cb,
                            (const char *   )"mqtt_client",
                            (unsigned short )1024,
                            (void *         )NULL,
                            (UBaseType_t    )RTOS_PRIORITY_LEVEL_2ST,
                            (TaskHandle_t * )&mqtt_client);

    if (pdPASS != xReturn){
        return pdFALSE;
    }

    return pdPASS;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
