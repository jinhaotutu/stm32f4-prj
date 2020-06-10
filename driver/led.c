/**
  *****************************************************************************
  * @file    : led.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 led driver
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


/* Defines --------------------------------------------------------------------*/
#define LED1_RCC_GLOUP  RCC_AHB1Periph_GPIOC
#define LED1_IO_GLOUP   GPIOC
#define LED1_IO_PIN     GPIO_Pin_0

#define LED1_ON     GPIO_ResetBits(LED1_IO_GLOUP, LED1_IO_PIN)
#define LED1_OFF    GPIO_SetBits(LED1_IO_GLOUP, LED1_IO_PIN)

/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/

/**
  * @note   Main program.
  * @brief  None
  * @param  None
  * @retval None
  */
void led_driver_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(LED1_RCC_GLOUP, ENABLE);

    /* LED GPIO口配置 */
    GPIO_InitStructure.GPIO_Pin = LED1_IO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED1_IO_GLOUP, &GPIO_InitStructure);

    LED1_OFF;
}

/**
  * @note   Main program.
  * @brief  None
  * @param  None
  * @retval None
  */
void led_driver_write(uint8_t *data, uint32_t len)
{
    uint8_t flag = *data;

    if (flag == 0){
        LED1_OFF;
    }else{
        LED1_ON;
    }
}

/**
  * @note   Main program.
  * @brief  None
  * @param  None
  * @retval None
  */
uint32_t led_driver_read(uint8_t *data, uint32_t max_len)
{
    uint8_t flag = 0;

    flag = GPIO_ReadOutputDataBit(LED1_IO_GLOUP, LED1_IO_PIN);

    return flag;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/

