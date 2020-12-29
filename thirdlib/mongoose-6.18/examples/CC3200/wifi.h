/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_MONGOOSE_EXAMPLES_CC3200_WIFI_H_
#define CS_MONGOOSE_EXAMPLES_CC3200_WIFI_H_

#include <stdbool.h>

bool wifi_setup_ap(const char *ssid, const char *pass, int channel);
bool wifi_setup_sta(const char *ssid, const char *pass);
void stop_nwp(void);

#endif /* CS_MONGOOSE_EXAMPLES_CC3200_WIFI_H_ */
