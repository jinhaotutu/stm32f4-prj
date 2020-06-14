/**
  *****************************************************************************
  * @file    : main.h
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32 config file
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-06-02
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* log */
#include "elog.h"

/* os */
#ifdef USE_OS
#include "FreeRTOSConfig.h"

#define RTOS_PRIORITY_HIGHEST       (10)
#define RTOS_PRIORITY_LEVEL_1ST     (9)
#define RTOS_PRIORITY_LEVEL_2ST     (8)
#define RTOS_PRIORITY_LEVEL_3ST     (7)
#define RTOS_PRIORITY_LEVEL_4ST     (6)
#define RTOS_PRIORITY_LEVEL_5ST     (5)
#endif

#ifdef __cplusplus
extern "C" {
#endif



/**
  *****************************************************************************
  * @version brief  :
  *****************************************************************************
  */


/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __CONFIG_H */

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

