/**
  *****************************************************************************
  * @file    : sys_config.c
  * @author  : Tuu
  * @version : 1.0.0
  * @date    : 2020-04-01
  * @brief   : stm32f407 system config
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
#include "sys_cfg.h"

/* Defines --------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/


/**
  * @note   rcc_config
  * @brief  system rcc_config
  * @param  None
  * @retval None
  */
static void rcc_config(void)
{
    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_WaitForHSEStartUp() != SUCCESS);

    /*
        * PLL_N = 336
        * PLL_M = 8
        * PLL_P = 2
        *
        * PLLP = 晶振 * PLL_N (PLL_M * PLL_P) = 8MHz * 336 / (8 * 2) = 168MHz
        */
    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08){}

    RCC_HCLKConfig(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div4);
    RCC_PCLK2Config(RCC_HCLK_Div2);
}

/**
  * @note   log_uart_init
  * @brief  uart0 init for system log
  * @param  None
  * @retval None
  */
static void log_uart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    /* USART1 GPIO口配置 */
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

    /* uart config */
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1,ENABLE);
}

/**
  * @note   Sys_Config
  * @brief  system init
  * @param  None
  * @retval None
  */
void Sys_Config(void)
{
    rcc_config();

    log_uart_init();

#ifdef USE_OS

#else
    extern void Delay_Config(void);
    Delay_Config();
#endif

    os_printf("***********STM32 System Config!***********");

    /* driver init */
    extern void led_driver_init(void);
    led_driver_init();

    /* thirdlib init */
    extern void easy_logger_init(void);
    easy_logger_init();
}

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef __GNUC__
int __io_putchar(int ch)
{
    USART_SendData(USART1, (u8) ch);

    while(!(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET));

    return ch;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
#else
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (u8) ch);

    while(!(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET));

    return ch;
}

int fgetc(FILE *f)
{
    while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET));

    return (USART_ReceiveData(USART1));
}
#endif

/**
  * @note   assert_failed
  * @brief  system fail log
  * @param  None
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    os_printf("assert_failed:[%s][%d]", file, line);

    while(1){
    }
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
