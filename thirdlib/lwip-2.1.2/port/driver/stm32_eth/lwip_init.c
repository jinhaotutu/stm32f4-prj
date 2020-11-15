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

/* Includes ------------------------------------------------------------------*/
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/tcp.h"
#include "lwip/tcpip.h"
#include "lwip/udp.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"
#include "lwip/priv/tcp_priv.h"

#include "config.h"
#include "ethernetif.h"

#include "lwip_init.h"
#include "eth_init.h"


#define __log_debug(...)    log_d(__VA_ARGS__)
#define __log_info(...)     log_i(__VA_ARGS__)

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    DHCP_START,
    DHCP_WAIT_ADDRESS,
    DHCP_ADDRESS_ASSIGNED,
    DHCP_TIMEOUT,
    DHCP_LINK_DOWN,
}DHCP_STA;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static struct netif gnetif;
static NET_CON_STATUS net_status = NET_STATUS_IDLE;

/* Private functions ---------------------------------------------------------*/
void LwIP_IRQ_Post(void)
{
    ethernetif_post(&gnetif);
}

/**
  * @brief  dhcp
  * @param  None
  * @retval None
  */
static void LwIP_DHCP_task(void *p)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;
    struct dhcp* dhcp;

    uint16_t timeout = 0;

    DHCP_STA dhcp_status = DHCP_START;

    while(1)
    {
        switch (dhcp_status)
        {
            case DHCP_START:
                net_status = NET_STATUS_DHCPING;
                __log_info("start dhcp ... ");
                dhcp_start(&gnetif);
                dhcp = netif_dhcp_data(&gnetif);
                /* IP address should be set to 0
                every time we want to assign a new DHCP address */
                dhcp_status = DHCP_WAIT_ADDRESS;

                break;

            case DHCP_WAIT_ADDRESS:
                /* Read the new IP address */
                if (dhcp->offered_ip_addr.addr != 0)
                {
                    dhcp_status = DHCP_ADDRESS_ASSIGNED;

                    __log_info("got dhcp ip");
                    ipaddr = dhcp->offered_ip_addr;
                    netmask = dhcp->offered_sn_mask;
                    gw = dhcp->offered_gw_addr;

                    /* Stop DHCP */
                    dhcp_stop(&gnetif);

                    __log_info("got ipadder: %s", inet_ntoa(ipaddr.addr));
                    __log_info("got netmask: %s", inet_ntoa(netmask.addr));
                    __log_info("got gwadder: %s", inet_ntoa(gw.addr));
                    netif_set_addr(&gnetif, &ipaddr , &netmask, &gw);

                    net_status = NET_STATUS_GOT_IP;

                    vTaskDelete(NULL);
                }
                else
                {
                    /* DHCP timeout */
                    if (timeout > 10)
                    {
                        dhcp_status = DHCP_TIMEOUT;

                        /* Stop DHCP */
                        dhcp_stop(&gnetif);

                        /* Static address used */
                        IP4_ADDR(&ipaddr, 192, 168, 100, 88);
                        IP4_ADDR(&netmask, 255, 255, 255, 0);
                        IP4_ADDR(&gw, 192, 168, 100, 1);
                        netif_set_addr(&gnetif, &ipaddr , &netmask, &gw);

                        __log_info("use static ip");
                        __log_info("got ipadder: %s", inet_ntoa(gnetif.ip_addr.addr));
                        __log_info("got netmask: %s", inet_ntoa(gnetif.netmask.addr));
                        __log_info("got gwadder: %s", inet_ntoa(gnetif.gw.addr));

                        net_status = NET_STATUS_GOT_IP;

                        vTaskDelete(NULL);
                    }
                    else
                    {
                        timeout++;
                    }
                }

                break;

            default:
                break;
        }

        /* wait 250 ms */
        sys_delay(250);
    }
}

/**
  * @brief  Link callback function, this function is called on change of link status.
  * @param  The network interface
  * @retval None
  */
void ETH_link_callback(struct netif *netif)
{
    if(netif_is_link_up(netif))
    {
        net_status = NET_STATUS_LINK_UP;

        /* When the netif is fully configured this function must be called.*/
        netif_set_up(&gnetif);
        __log_debug("netif_set_up");

        sys_thread_new("dhcp", LwIP_DHCP_task, NULL, 1024, (configMAX_PRIORITIES - 3));
    }
    else
    {
        net_status = NET_STATUS_LINK_DOWN;

        /*  When the netif link is down this function must be called.*/
        netif_set_down(&gnetif);
        __log_debug("netif_set_down");
    }
}

static void LwIP_loop_task(void *p)
{
    uint32_t EthStatus = 0;

    ip_addr_t ipaddr={0};
    ip_addr_t netmask={0};
    ip_addr_t gw={0};

    /* eth init */
    net_status = NET_STATUS_CONFIG;

    EthStatus = ETH_BSP_Config();
    __log_debug("EthStatus:0x%02x", EthStatus);

    tcpip_init(NULL, NULL);

    /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
    struct ip_addr *netmask, struct ip_addr *gw,
    void *state, err_t (* init)(struct netif *netif),
    err_t (* input)(struct pbuf *p, struct netif *netif))

    Adds your network interface to the netif_list. Allocate a struct
    netif and pass a pointer to this structure as the first argument.
    Give pointers to cleared ip_addr structures when using DHCP,
    or fill them with sane numbers otherwise. The state pointer may be NULL.

    The init function pointer must point to a initialization function for
    your ethernet netif interface. The following code illustrates it's use.*/
    netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input);

    /*  Registers the default network interface.*/
    netif_set_default(&gnetif);

    if (EthStatus == (ETH_INIT_FLAG | ETH_LINK_FLAG))
    {
        net_status = NET_STATUS_LINK_UP;
        __log_debug("netif_set_up");
        /* Set Ethernet link flag */
        gnetif.flags |= NETIF_FLAG_LINK_UP;

        /* When the netif is fully configured this function must be called.*/
        netif_set_up(&gnetif);

        sys_thread_new("dhcp", LwIP_DHCP_task, NULL, 1024, (configMAX_PRIORITIES - 3));
    }
    else
    {
        net_status = NET_STATUS_LINK_DOWN;
        /*  When the netif link is down this function must be called.*/
        netif_set_down(&gnetif);
    }

    /* Set the link callback function, this function is called on change of link status*/
    netif_set_link_callback(&gnetif, ETH_link_callback);

    uint8_t flag = 0;
    while(1)
    {
        /* 循环检测网线通断 */
        if(ETH_Get_Link_Status())
        {
            flag = 1;
            network_led_write(&flag, 1);
            netif_set_link_up(&gnetif);
        }
        else
        {
            flag = 0;
            network_led_write(&flag, 1);
            netif_set_link_down(&gnetif);
        }

        sys_delay(100);
    }
}

/**
* @brief  Initializes the lwIP stack
* @param  None
* @retval None
*/
int NetWork_Init(void)
{
    sys_thread_new("dhcp", LwIP_loop_task, NULL, 1024, (configMAX_PRIORITIES - 2));

    return 0;
}

NET_CON_STATUS get_net_status(void)
{
    return net_status;
}

/************************ (C) COPYRIGHT Tuu ********END OF FILE****************/
