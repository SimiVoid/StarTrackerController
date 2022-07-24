#ifndef __BT_H__
#define __BT_H__

#include <stdint.h>

#include "esp_spp_api.h"
#include "esp_gap_bt_api.h"

#define BT_DEVICE_NAME "StarTrackerController"
#define SPP_SERVER_NAME "StarTrackerControllerServer"
#define BT_4_PIN "1234"

#define SPP_SHOW_DATA 0
#define SPP_SHOW_SPEED 1
#define SPP_SHOW_MODE SPP_SHOW_SPEED

void vTaskBT(void* pvParameters);

#endif