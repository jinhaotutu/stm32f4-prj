/**
  *****************************************************************************
  * @file    : main.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 main
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-06-02
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "config.h"
#include "main.h"

#include "sys_cfg.h"
#include "sys_delay.h"


/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
extern void user_main(void *p);

/**
  * @note   Main program.
  * @brief  None
  * @param  None
  * @retval None
  */
int main(void)
{
    /* stm32系统配置 */
    Sys_Config();

#ifdef USE_OS

#else
    user_main(NULL);
#endif

    while(1)
    {
#ifdef USE_OS
        log_e("never get here");
#else
        log_d("led on");
        delay_ms(1000);

        log_d("led off");
        delay_ms(1000);
#endif
    }
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

