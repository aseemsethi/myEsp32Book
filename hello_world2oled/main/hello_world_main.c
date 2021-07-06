/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <nvs_flash.h>
#include "driver/gpio.h"
#include "esp_log.h"  // for ESP_LOGE
void task_test_SSD1306i2c(void *ignore);


void app_main(void)
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    fflush(stdout);
    int lvl = 0;
    // This is the new U8g2 driver; works for inbuilt OLED on WEMOS TTGO
    task_test_SSD1306i2c(NULL);
    while(1) {
        TickType_t xDelay = 500 / portTICK_PERIOD_MS;
        vTaskDelay(xDelay);
        
        lvl=gpio_get_level(22);
        if (lvl == 1) {
            printf("\n Boot button pressed - erase flash !!!");
            nvs_flash_erase();
        }
    }
}
