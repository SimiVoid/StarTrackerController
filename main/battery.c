#include "battery.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static const char* TAG = "battery";
static float battery_voltage;

void vTaskBattery(void* pvParameters) {
    #if BATTERY_ADC_UNIT == ADC_UNIT_1
        adc1_config_channel_atten(BATTERY_ADC_CHANNEL, ADC_ATTEN_DB_11);
    #elif BATTERY_ADC_UNIT == ADC_UNIT_2
        adc2_config_channel_atten(BATTERY_ADC_CHANNEL, ADC_ATTEN_DB_11);
    #else
        #error "Invalid ADC unit"
    #endif

    battery_voltage = 0.f;

    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_characterize(BATTERY_ADC_UNIT, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc_chars);

    ESP_LOGI(TAG, "Battery voltage sensor started");

    while (1) {
        uint32_t raw_value = 0;

        #if BATTERY_ADC_UNIT == ADC_UNIT_1
            adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
            raw_value = adc1_get_raw(BATTERY_ADC_CHANNEL);
        #elif BATTERY_ADC_UNIT == ADC_UNIT_2
            adc2_config_width(ADC_WIDTH_BIT_DEFAULT);
            raw_value = adc2_get_raw(BATTERY_ADC_CHANNEL);
        #else
            #error "Invalid ADC unit"
        #endif

        battery_voltage = esp_adc_cal_raw_to_voltage(raw_value, &adc_chars) * VOLTAGE_DIVIDER_RATIO / 1000.f;
        ESP_LOGD(TAG, "Battery voltage: %.2fV", battery_voltage);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

float getBatteryVoltage(void) {
    return battery_voltage;
}