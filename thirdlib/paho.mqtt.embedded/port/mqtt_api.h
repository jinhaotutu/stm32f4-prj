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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  MQTT_API_H
#define  MQTT_API_H

/* Includes -------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __EXTERN_GLOBAL
    #define __EXTERN
#else
    #define __EXTERN extern
#endif

/**
  *****************************************************************************
  * @version brief  :
  *****************************************************************************
  */


/* Defines --------------------------------------------------------------------*/


/* Types ----------------------------------------------------------------------*/
typedef int (*mqtt_msg)(const char *topic, int topic_len, const char *data, int data_len);

/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
int mqtt_subscribe(const char *topic, char qos);
int mqtt_publish(const char *topic, char qos, const char *data, int len);
int mqtt_client_exit(void);
int mqtt_client_connect(const char *url, int port, const char *id, const char *user, const char *password, mqtt_msg cb);

#ifdef __cplusplus
}
#endif

#endif /* MQTT_API_H */

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
