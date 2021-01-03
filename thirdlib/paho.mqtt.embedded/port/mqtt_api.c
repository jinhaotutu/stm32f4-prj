#include "MQTTClient.h"

#define MQTT_BUF_LEN    512

typedef int (*mqtt_msg)(const char *topic, int topic_len, const char *data, int data_len);

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

static void messageArrived(MessageData *md)
{
    MQTTMessage *message = md->message;

    if (NULL != mq_opts.cb){
        mq_opts.cb(md->topicName->lenstring.data, md->topicName->lenstring.len,
                    message->payload, message->payloadlen);
    }
}

int mqtt_subscribe(const char *topic, char qos)
{
    printf("Subscribing to %s\n", topic);
    return MQTTSubscribe(&(mq_opts.c), topic, qos, messageArrived);
}

int mqtt_publish(const char *topic, char qos, const char *data, int len)
{
    printf("Publish to %s\n", topic);

    MQTTMessage message={0};
    message.qos = qos;
    message.payload = (void *)data;
    message.payloadlen = len;
    return MQTTPublish(&(mq_opts.c), topic, &message);
}

int mqtt_client_exit(void)
{
    printf("exit\n");

    MQTTDisconnect(&(mq_opts.c));
    NetworkDisconnect(&(mq_opts.n));

    return 0;
}

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

    ret = MQTTClientInit(&(mq_opts.c), &(mq_opts.n), 1000, mq_opts.send_buf, MQTT_BUF_LEN, mq_opts.recv_buf, MQTT_BUF_LEN);
    if (0 != ret){
        goto exit;
    }
    printf("mqtt init succees\n");

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
        goto exit;
    }
    printf("mqtt connect succees\n");

    return 0;

exit:
    mqtt_client_exit();

    return ret;
}

int mqtt_loop(void)
{
    return MQTTYield(&(mq_opts.c), 1000);
}


/////

int mqtt_topic_parse(const char *topic, int topic_len, const char *data, int data_len)
{
    printf("topic:%.*s\n", topic_len, topic);
    printf("payload:%.*s\n", data_len, data);

    return 0;
}


void mqtt_demo(void *p)
{
    mqtt_client_connect("10.6.5.215", 1883, "pid/sn", "pid", "sn+dsk+psk", mqtt_topic_parse);

    mqtt_subscribe("pid/sn/things/v1/model/#", 0);

    while(1)
    {
        mqtt_loop();

        IMOU_sleepMs(5000);
        mqtt_publish("pid/sn/things/v1/model/set", 0, "hello world", strlen("hello world"));
        mqtt_publish("pid/sn/things/v1/model/get", 0, "see you", strlen("see you"));
    }

    mqtt_client_exit();
}

int mqtt_start(void)
{
    void*p;
    IMOU_createThread(&p, mqtt_demo, NULL);

    while(1)
    {
        IMOU_sleepMs(1000);
    }

    return 0;
}

