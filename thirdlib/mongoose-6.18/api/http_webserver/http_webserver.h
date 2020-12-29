/**
  *****************************************************************************
  * @file    : http_webserver.h
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-12-29
  * @brief   : mongoose http webserver api
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-12-29
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __HTTP_WEBSERVER_H
#define  __HTTP_WEBSERVER_H

/* Includes -------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
  *****************************************************************************
  * @version brief  :
  *****************************************************************************
  */


/* Defines --------------------------------------------------------------------*/


/* Types ----------------------------------------------------------------------*/
typedef int (*response)(const void *nc, const void *data, size_t len);

typedef struct rsp_type
{
    /* data */
    void *nc;
    response send;
}rsp_type;

typedef int (*server_user)(const char *user_data, int len, const rsp_type *rsp);

/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
int http_webserver(const char *port, const char *path, server_user cb);

#ifdef __cplusplus
}
#endif

#endif /* __HTTP_WEBSERVER_H */

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
