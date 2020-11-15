/**
  *****************************************************************************
  * @file    : sys_delay.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 system delay config
  ******************************************************************************
  * @lasteditors  : Tuu
  * @lasteditTime : 2020-06-02
  ******************************************************************************
  * @atten   : Copyright (C) by Tuu Inc
  *
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/

#ifndef USE_OS
/**
  * @note   Delay_Config
  * @brief  None
  * @param  None
  * @retval None
  */
void Delay_Config(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    uint32_t reload = SystemCoreClock / 1000000 - 1;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->LOAD = reload;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/**
  * @note   delay_ms
  * @brief  None
  * @param  None
  * @retval None
  */
void delay_ms(vu32 nTime)
{
    nTime *= 1000;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;        //使能SysTick，开始计数
    while(nTime--){
        while((SysTick->CTRL&0X010000) == 0);        //等待COUNTFLAG标志位置1
    }
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);     //失能SysTick，停止计数
}

/**
  * @note   delay_us
  * @brief  None
  * @param  None
  * @retval None
  */
void delay_us(vu32 nTime)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while(nTime--){
        while((SysTick->CTRL&0X010000) == 0);
    }
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}
#endif

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
