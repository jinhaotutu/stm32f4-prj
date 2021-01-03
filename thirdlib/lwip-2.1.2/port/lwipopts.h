/**
  ******************************************************************************
  * @file    lwipopts.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    31-July-2013
  * @brief   lwIP Options Configuration.
  *          This file is based on Utilities\lwip_v1.4.1\src\include\lwip\opt.h 
  *          and contains the lwIP configuration for the STM32F4x7 demonstration.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define USE_LWIP

#define LWIP_SOCKET_POLL    0

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT    0

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#include "FreeRTOSConfig.h"
#ifdef USE_OS
#define NO_SYS                  0
#else
#define NO_SYS                  1
#endif

/**
 * NO_SYS_NO_TIMERS==1: Drop support for sys_timeout when NO_SYS==1
 * Mainly for compatibility to old versions.
 */
#define NO_SYS_NO_TIMERS        1

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                (10*1024)

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF           100
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 6
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        12
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT    10


/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          10

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       500


/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         0

/* TCP Maximum segment size. */
#define TCP_MSS                 (1500 - 40)/* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (4*TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */

#define TCP_SND_QUEUELEN        (2* TCP_SND_BUF/TCP_MSS)

/* TCP receive window. */
#define TCP_WND                 (2*TCP_MSS)


/* ---------- ICMP options ---------- */
#define LWIP_ICMP                       1


/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               1

#define LWIP_NETIF_HOSTNAME     1


/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255


/* ---------- Statistics options ---------- */
#define LWIP_STATS 0
#define LWIP_PROVIDE_ERRNO

/* ---------- link callback options ---------- */
/* LWIP_NETIF_LINK_CALLBACK==1: Support a callback function from an interface
 * whenever the link changes (i.e., link down)
 */
#define LWIP_NETIF_LINK_CALLBACK        1

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/

/* 
The STM32F4x7 allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
#define CHECKSUM_BY_HARDWARE 


#ifdef CHECKSUM_BY_HARDWARE
  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 0
  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                0
  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                0 
  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               0
  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              0
  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              0
  /* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
  #define CHECKSUM_GEN_ICMP               0
#else
  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
  #define CHECKSUM_GEN_IP                 1
  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
  #define CHECKSUM_GEN_UDP                1
  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
  #define CHECKSUM_GEN_TCP                1
  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
  #define CHECKSUM_CHECK_IP               1
  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
  #define CHECKSUM_CHECK_UDP              1
  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
  #define CHECKSUM_CHECK_TCP              1
  /* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
  #define CHECKSUM_GEN_ICMP               1
#endif


/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#if NO_SYS
#define LWIP_NETCONN                    0
#else
#define LWIP_NETCONN                    1
#endif

/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#if NO_SYS
#define LWIP_SOCKET                     0
#else
#define LWIP_SOCKET                     1
#endif

#define LWIP_DNS                        1

#if !NO_SYS
#define TCPIP_THREAD_NAME              "TCP/IP"
#define TCPIP_THREAD_STACKSIZE          1000
#define TCPIP_MBOX_SIZE                 5
#define DEFAULT_UDP_RECVMBOX_SIZE       2000
#define DEFAULT_TCP_RECVMBOX_SIZE       2000
#define DEFAULT_ACCEPTMBOX_SIZE         2000
#define DEFAULT_THREAD_STACKSIZE        500
#define TCPIP_THREAD_PRIO               (configMAX_PRIORITIES - 2)
#define LWIP_COMPAT_MUTEX               1
#define LWIP_COMPAT_MUTEX_ALLOWED       1
#endif

#define LWIP_SO_SNDTIMEO                1
#define LWIP_SO_RCVTIMEO                1

/*
   ----------------------------------------
   ---------- Lwip Debug options ----------
   ----------------------------------------
*/
#define LWIP_DEBUG                      1

#define LWIP_TIMEVAL_PRIVATE            1
#if !LWIP_TIMEVAL_PRIVATE
#include <sys/time.h>
#endif

#define MEMP_NUM_NETCONN                6

/**
 * LWIP_DBG_MIN_LEVEL: After masking, the value of the debug is
 * compared against this value. If it is smaller, then debugging
 * messages are written.
 */
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_OFF

/**
 * LWIP_DBG_TYPES_ON: A mask that can be used to globally enable/disable
 * debug messages of certain types.
 */
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON

/**
 * ETHARP_DEBUG: Enable debugging in etharp.c.
 */
#define ETHARP_DEBUG                    LWIP_DBG_OFF

/**
 * NETIF_DEBUG: Enable debugging in netif.c.
 */
#define NETIF_DEBUG                     LWIP_DBG_OFF

/**
 * PBUF_DEBUG: Enable debugging in pbuf.c.
 */
#define PBUF_DEBUG                      LWIP_DBG_OFF

/**
 * API_LIB_DEBUG: Enable debugging in api_lib.c.
 */
#define API_LIB_DEBUG                   LWIP_DBG_OFF

/**
 * API_MSG_DEBUG: Enable debugging in api_msg.c.
 */
#define API_MSG_DEBUG                   LWIP_DBG_OFF

/**
 * SOCKETS_DEBUG: Enable debugging in sockets.c.
 */
#define SOCKETS_DEBUG                   LWIP_DBG_OFF

/**
 * ICMP_DEBUG: Enable debugging in icmp.c.
 */
#define ICMP_DEBUG                      LWIP_DBG_OFF

/**
 * IGMP_DEBUG: Enable debugging in igmp.c.
 */
#define IGMP_DEBUG                      LWIP_DBG_OFF

/**
 * INET_DEBUG: Enable debugging in inet.c.
 */
#define INET_DEBUG                      LWIP_DBG_OFF

/**
 * IP_DEBUG: Enable debugging for IP.
 */
#define IP_DEBUG                        LWIP_DBG_OFF

/**
 * IP_REASS_DEBUG: Enable debugging in ip_frag.c for both frag & reass.
 */
#define IP_REASS_DEBUG                  LWIP_DBG_OFF

/**
 * RAW_DEBUG: Enable debugging in raw.c.
 */
#define RAW_DEBUG                       LWIP_DBG_OFF

/**
 * MEM_DEBUG: Enable debugging in mem.c.
 */
#define MEM_DEBUG                       LWIP_DBG_OFF

/**
 * MEMP_DEBUG: Enable debugging in memp.c.
 */
#define MEMP_DEBUG                      LWIP_DBG_OFF

/**
 * SYS_DEBUG: Enable debugging in sys.c.
 */
#define SYS_DEBUG                       LWIP_DBG_OFF

/**
 * TIMERS_DEBUG: Enable debugging in timers.c.
 */
#define TIMERS_DEBUG                    LWIP_DBG_OFF

/**
 * TCP_DEBUG: Enable debugging for TCP.
 */
#define TCP_DEBUG                       LWIP_DBG_OFF

/**
 * TCP_INPUT_DEBUG: Enable debugging in tcp_in.c for incoming debug.
 */
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF

/**
 * TCP_FR_DEBUG: Enable debugging in tcp_in.c for fast retransmit.
 */
#define TCP_FR_DEBUG                    LWIP_DBG_OFF

/**
 * TCP_RTO_DEBUG: Enable debugging in TCP for retransmit
 * timeout.
 */
#define TCP_RTO_DEBUG                   LWIP_DBG_OFF

/**
 * TCP_CWND_DEBUG: Enable debugging for TCP congestion window.
 */
#define TCP_CWND_DEBUG                  LWIP_DBG_OFF

/**
 * TCP_WND_DEBUG: Enable debugging in tcp_in.c for window updating.
 */
#define TCP_WND_DEBUG                   LWIP_DBG_OFF

/**
 * TCP_OUTPUT_DEBUG: Enable debugging in tcp_out.c output functions.
 */
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF

/**
 * TCP_RST_DEBUG: Enable debugging for TCP with the RST message.
 */
#define TCP_RST_DEBUG                   LWIP_DBG_OFF

/**
 * TCP_QLEN_DEBUG: Enable debugging for TCP queue lengths.
 */
#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF

/**
 * UDP_DEBUG: Enable debugging in UDP.
 */
#define UDP_DEBUG                       LWIP_DBG_OFF

/**
 * TCPIP_DEBUG: Enable debugging in tcpip.c.
 */
#define TCPIP_DEBUG                     LWIP_DBG_OFF

/**
 * PPP_DEBUG: Enable debugging for PPP.
 */
#define PPP_DEBUG                       LWIP_DBG_OFF

/**
 * SLIP_DEBUG: Enable debugging in slipif.c.
 */
#define SLIP_DEBUG                      LWIP_DBG_OFF

/**
 * DHCP_DEBUG: Enable debugging in dhcp.c.
 */
#define DHCP_DEBUG                      LWIP_DBG_OFF

/**
 * AUTOIP_DEBUG: Enable debugging in autoip.c.
 */
#define AUTOIP_DEBUG                    LWIP_DBG_OFF

/**
 * SNMP_MSG_DEBUG: Enable debugging for SNMP messages.
 */
#define SNMP_MSG_DEBUG                  LWIP_DBG_OFF

/**
 * SNMP_MIB_DEBUG: Enable debugging for SNMP MIBs.
 */
#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF

/**
 * DNS_DEBUG: Enable debugging for DNS.
 */
#define DNS_DEBUG                       LWIP_DBG_OFF

#endif /* __LWIPOPTS_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
