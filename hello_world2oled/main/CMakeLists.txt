idf_component_register(SRCS "hello_world_main.c" "oled.c" "u8g2_esp32_hal.c"
                       INCLUDE_DIRS "."
                    REQUIRES u8g2 nvs_flash esp_http_server mqtt spiffs json)