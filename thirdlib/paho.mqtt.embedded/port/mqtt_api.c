/**
  *****************************************************************************
  * @file    : mqtt_api.h
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2021-01-03
  * @brief   : stm32f407 mqtt api
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2021-01-03
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is mqtt api
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MQTTClient.h"
#include "mqtt_api.h"

/* Private define ------------------------------------------------------------*/
#define MQTT_BUF_LEN    512

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
typedef struct mqtt_opt
{
    /* data */
    MQTTClient c;
    Network n;
    unsigned char send_buf[MQTT_BUF_LEN];
    unsigned char recv_buf[MQTT_BUF_LEN];
    mqtt_msg cb;
}mqtt_opt;
static mqtt_opt mq_opts;


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
static void messageArrived(MessageData *md)
{
    MQTTMessage *message = md->message;

    if (NULL != mq_opts.cb){
        mq_opts.cb(md->topicName->lenstring.data, md->topicName->lenstring.len,
                    message->payload, message->payloadlen);
    }
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
int mqtt_subscribe(const char *topic, char qos)
{
    printf("Subscribing to %s\n", topic);
    return MQTTSubscribe(&(mq_opts.c), topic, qos, messageArrived);
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
int mqtt_publish(const char *topic, char qos, const char *data, int len)
{
    printf("Publish to %s\n", topic);

    MQTTMessage message={0};
    message.qos = qos;
    message.payload = (void *)data;
    message.payloadlen = len;
    return MQTTPublish(&(mq_opts.c), topic, &message);
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
int mqtt_client_exit(void)
{
    printf("exit\n");

    MQTTDisconnect(&(mq_opts.c));
    NetworkDisconnect(&(mq_opts.n));

    return 0;
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
int mqtt_client_connect(const char *url, int port, const char *id, const char *user, const char *password, mqtt_msg cb)
{
    if (NULL == url){
        return -1;
    }

    int ret = 0;

    memset(&mq_opts, 0, sizeof(mqtt_opt));
    mq_opts.cb = cb;

    NetworkInit(&(mq_opts.n));
    ret = NetworkConnect(&(mq_opts.n), (char *)url, port);
    if (0 != ret){
        goto exit;
    }
    printf("connect succees\n");

    MQTTClientInit(&(mq_opts.c), &(mq_opts.n), 1000, mq_opts.send_buf, MQTT_BUF_LEN, mq_opts.recv_buf, MQTT_BUF_LEN);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.willFlag = 0;
    data.MQTTVersion = 3;
    data.clientID.cstring = (char *)id;
    data.username.cstring = (char *)user;
    data.password.cstring = (char *)password;
    data.keepAliveInterval = 60;
    data.cleansession = 1;

    ret = MQTTConnect(&(mq_opts.c), &data);
    if (0 != ret){
        printf("mqtt conn error\n");
        goto exit;
    }
    printf("mqtt connect succees\n");

#ifdef MQTT_TASK
    MQTTStartTask(&(mq_opts.c));
#endif

    printf("mqtt init succees\n");

    return 0;

exit:
    mqtt_client_exit();

    return ret;
}

/**
  * @note   tcp_server_cb
  * @brief  This function is used to run app task
  * @param  *p
  * @retval None
  */
int mqtt_loop(void)
{
    return MQTTYield(&(mq_opts.c), 1000);
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
