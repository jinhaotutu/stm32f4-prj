/**
  *****************************************************************************
  * @file    : eth_init.h
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
  * this is stm32 eth init api for user code
  *****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  ETH_INIT_H
#define  ETH_INIT_H

/* Includes -------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4x7_eth.h"

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

/* Uncomment the line below when using time stamping and/or IPv4 checksum offload */
#define USE_ENHANCED_DMA_DESCRIPTORS

/* Uncomment the line below if you want to use user defined Delay function
    (for precise timing), otherwise default _eth_delay_ function defined within
    the Ethernet driver is used (less precise timing) */
// #define USE_Delay

/*This define allow to customize configuration of the Ethernet driver buffers */
#define CUSTOM_DRIVER_BUFFERS_CONFIG


#ifdef USE_Delay
    #define _eth_delay_    os_delay     /* User can provide more timing precise _eth_delay_ function */
                                        /* in this example Systick is configured with an interrupt every 10 ms*/
#else
    #define _eth_delay_    ETH_Delay    /* Default _eth_delay_ function with less precise timing */
#endif


#ifdef  CUSTOM_DRIVER_BUFFERS_CONFIG
/* Redefinition of the Ethernet driver buffers size and count */
    #define ETH_RX_BUF_SIZE    ETH_MAX_PACKET_SIZE  /* buffer size for receive */
    #define ETH_TX_BUF_SIZE    ETH_MAX_PACKET_SIZE  /* buffer size for transmit */
    #define ETH_RXBUFNB        4                    /* 4 Rx buffers of size ETH_RX_BUF_SIZE */
    #define ETH_TXBUFNB        4                    /* 4 Tx buffers of size ETH_TX_BUF_SIZE */
#endif

/* PHY configuration section **************************************************/
#ifdef USE_Delay
/* PHY Reset delay */ 
#define PHY_RESET_DELAY    ((uint32_t)0x0000010F)
/* PHY Configuration delay */
#define PHY_CONFIG_DELAY   ((uint32_t)0x00000FFF)
/* Delay when writing to Ethernet registers*/
#define ETH_REG_WRITE_DELAY ((uint32_t)0x00000001)
#else
/* PHY Reset delay */ 
#define PHY_RESET_DELAY    ((uint32_t)0x000FFFFF)
/* PHY Configuration delay */ 
#define PHY_CONFIG_DELAY   ((uint32_t)0x00FFFFFF)
/* Delay when writing to Ethernet registers*/
#define ETH_REG_WRITE_DELAY ((uint32_t)0x0000FFFF)
#endif

#define AUTONEGOTIATION         1

#define ENABLE_RCC_INIT         0

/* These values are relatives to LAN8720 PHY and change from PHY to another,
    so the user have to update this value depending on the used external PHY */

/* The LAN8720 PHY status register  */
#define PHY_SR                 ((uint16_t)31)           /* PHY special status register Offset */
#define PHY_SPEED_STATUS       ((uint16_t)1<<(3-1))     /* PHY Speed mask */
#define PHY_DUPLEX_STATUS      ((uint16_t)1<<(13-1))    /* PHY Duplex mask */

/* Note : Common PHY registers are defined in stm32f4x7_eth.h file */

/* eth config */
#define RMII_MODE

#define PHY_ADDRESS             0x01

/* Ethernet Flags for EthStatus variable */
#define ETH_INIT_FLAG           0x01 /* Ethernet Init Flag */
#define ETH_LINK_FLAG           0x10 /* Ethernet Link Flag */

/* Types ----------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/

/**
  * @note   ETH_BSP_Config
  * @brief  Configures the Ethernet
  * @param  None
  * @retval None
  */
uint32_t ETH_BSP_Config(void);

/**
  * @note   ETH_Get_Link_Status
  * @brief  Get Ethernet link status
  * @param  None
  * @retval None
  */
uint8_t ETH_Get_Link_Status(void);

#ifdef __cplusplus
}
#endif

#endif /* ETH_INIT_H */

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
