#include "wifi.h"

#include "mongoose.h"

#include <simplelink/cc_pal.h>
#include <simplelink/include/wlan.h>

#include <inc/hw_types.h>

#include <driverlib/gpio.h>
#include <driverlib/utils.h>

#include <example/common/gpio_if.h>
#include "cs_dbg.h"

void SimpleLinkWlanEventHandler(SlWlanEvent_t *e) {
  switch (e->Event) {
    case SL_WLAN_CONNECT_EVENT:
      LOG(LL_INFO, ("WiFi: connected, getting IP"));
      break;
    case SL_WLAN_STA_CONNECTED_EVENT:
      LOG(LL_INFO, ("WiFi: station connected"));
      break;
    case SL_WLAN_STA_DISCONNECTED_EVENT:
      LOG(LL_INFO, ("WiFi: station disconnected"));
      break;
    default:
      LOG(LL_INFO, ("WiFi: event %d", (int) e->Event));
  }
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *e) {
  if (e->Event == SL_NETAPP_IPV4_IPACQUIRED_EVENT) {
    SlIpV4AcquiredAsync_t *ed = &e->EventData.ipAcquiredV4;
    LOG(LL_INFO, ("IP acquired: %lu.%lu.%lu.%lu", SL_IPV4_BYTE(ed->ip, 3),
                  SL_IPV4_BYTE(ed->ip, 2), SL_IPV4_BYTE(ed->ip, 1),
                  SL_IPV4_BYTE(ed->ip, 0)));
    GPIO_IF_LedToggle(MCU_RED_LED_GPIO);
  } else if (e->Event == SL_NETAPP_IP_LEASED_EVENT) {
    LOG(LL_INFO, ("IP leased"));
  } else {
    LOG(LL_INFO, ("NetApp event %d", (int) e->Event));
  }
}

bool wifi_setup_ap(const char *ssid, const char *pass, int channel) {
  uint8_t v;
  if (sl_WlanSetMode(ROLE_AP) != 0) {
    return false;
  }
  if (sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_SSID, strlen(ssid),
                 (const uint8_t *) ssid) != 0) {
    return false;
  }
  v = strlen(pass) > 0 ? SL_SEC_TYPE_WPA : SL_SEC_TYPE_OPEN;
  if (sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_SECURITY_TYPE, 1, &v) != 0) {
    return false;
  }
  if (v == SL_SEC_TYPE_WPA &&
      sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_PASSWORD, strlen(pass),
                 (const uint8_t *) pass) != 0) {
    return false;
  }
  v = channel;
  if (sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_CHANNEL, 1, &v) != 0) {
    return false;
  }
  sl_NetAppStop(SL_NET_APP_DHCP_SERVER_ID);
  {
    SlNetCfgIpV4Args_t ipcfg;
    memset(&ipcfg, 0, sizeof(ipcfg));
    if (!inet_pton(AF_INET, "192.168.4.1", &ipcfg.ipV4) ||
        !inet_pton(AF_INET, "255.255.255.0", &ipcfg.ipV4Mask) ||
        /* This means "disable". 0.0.0.0 won't do. */
        !inet_pton(AF_INET, "255.255.255.255", &ipcfg.ipV4DnsServer) ||
        /* We'd like to disable gateway too, but DHCP server refuses to start.
           */
        !inet_pton(AF_INET, "192.168.4.1", &ipcfg.ipV4Gateway) ||
        sl_NetCfgSet(SL_IPV4_AP_P2P_GO_STATIC_ENABLE, IPCONFIG_MODE_ENABLE_IPV4,
                     sizeof(ipcfg), (uint8_t *) &ipcfg) != 0) {
      return false;
    }
  }
  {
    SlNetAppDhcpServerBasicOpt_t dhcpcfg;
    memset(&dhcpcfg, 0, sizeof(dhcpcfg));
    dhcpcfg.lease_time = 900;
    if (!inet_pton(AF_INET, "192.168.4.20", &dhcpcfg.ipv4_addr_start) ||
        !inet_pton(AF_INET, "192.168.4.200", &dhcpcfg.ipv4_addr_last) ||
        sl_NetAppSet(SL_NET_APP_DHCP_SERVER_ID, NETAPP_SET_DHCP_SRV_BASIC_OPT,
                     sizeof(dhcpcfg), (uint8_t *) &dhcpcfg) != 0) {
      return false;
    }
  }
  sl_Stop(0);
  sl_Start(NULL, NULL, NULL);
  if (sl_NetAppStart(SL_NET_APP_DHCP_SERVER_ID) != 0) {
    LOG(LL_ERROR, ("DHCP server failed to start"));
    return false;
  }
  LOG(LL_INFO, ("WiFi: AP %s configured, IP 192.168.4.1", ssid));
  return true;
}

bool wifi_setup_sta(const char *ssid, const char *pass) {
  SlSecParams_t sp;
  LOG(LL_INFO, ("WiFi: connecting to %s", ssid));
  if (sl_WlanSetMode(ROLE_STA) != 0) return false;
  sl_Stop(0);
  sl_Start(NULL, NULL, NULL);
  sl_WlanDisconnect();
  sp.Key = (_i8 *) pass;
  sp.KeyLen = strlen(pass);
  sp.Type = sp.KeyLen ? SL_SEC_TYPE_WPA : SL_SEC_TYPE_OPEN;
  if (sl_WlanConnect((const _i8 *) ssid, strlen(ssid), 0, &sp, 0) != 0) {
    return false;
  }
  return true;
}

/*
 * In SDK 1.2.0 TI decided to stop resetting NWP before sl_Start, which in
 * practice means that sl_start will hang on subsequent runs after the first.
 *
 * See this post for details and suggested solution:
 * https://e2e.ti.com/support/wireless_connectivity/simplelink_wifi_cc31xx_cc32xx/f/968/p/499123/1806610#1806610
 *
 * However, since they don't provide OS_debug variant of simplelink.a and
 * adding another project dependency will complicate our demo even more,
 * we just take the required bit of code.
 *
 * This is a copy-paste of NwpPowerOnPreamble from cc_pal.c.
 */
void stop_nwp(void) {
#define MAX_RETRY_COUNT 1000
  unsigned int sl_stop_ind, apps_int_sts_raw, nwp_lpds_wake_cfg;
  unsigned int retry_count;
  /* Perform the sl_stop equivalent to ensure network services
     are turned off if active */
  HWREG(0x400F70B8) = 1; /* APPs to NWP interrupt */
  UtilsDelay(800000 / 5);

  retry_count = 0;
  nwp_lpds_wake_cfg = HWREG(0x4402D404);
  sl_stop_ind = HWREG(0x4402E16C);

  if ((nwp_lpds_wake_cfg != 0x20) && /* Check for NWP POR condition */
      !(sl_stop_ind & 0x2))          /* Check if sl_stop was executed */
  {
    /* Loop until APPs->NWP interrupt is cleared or timeout */
    while (retry_count < MAX_RETRY_COUNT) {
      apps_int_sts_raw = HWREG(0x400F70C0);
      if (apps_int_sts_raw & 0x1) {
        UtilsDelay(800000 / 5);
        retry_count++;
      } else {
        break;
      }
    }
  }
  HWREG(0x400F70B0) = 1; /* Clear APPs to NWP interrupt */
  UtilsDelay(800000 / 5);

  /* Stop the networking services */
  NwpPowerOff();
}
