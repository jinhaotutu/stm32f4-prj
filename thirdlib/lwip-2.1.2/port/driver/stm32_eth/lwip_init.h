/**
  *****************************************************************************
  * @file    : lwip_init.h
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 eth init api
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-11-01
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  * this is lwip init for stm32
  *****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  LWIP_INIT_H
#define  LWIP_INIT_H

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
typedef unsigned int NET_CON_STATUS;
#define NET_STATUS_IDLE        0
#define NET_STATUS_CONFIG      1
#define NET_STATUS_LINK_DOWN   2
#define NET_STATUS_LINK_UP     3
#define NET_STATUS_DHCPING     4
#define NET_STATUS_GOT_IP      5

/* Types ----------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
int NetWork_Init(void);

NET_CON_STATUS get_net_status(void);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_INIT_H */

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

