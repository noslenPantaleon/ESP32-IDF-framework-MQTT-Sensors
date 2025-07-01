#include <stdio.h>
#include <string.h>
#include "mqtt_app.h"
#include "dht_app.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include <unistd.h>

#include "oled_display.h"

#define FORMAT_DATA "H:%.2f%% T:%.2fC"
#define TEMPERATURE_TOPIC "/topic/temperature"
#define HUMIDITY_TOPIC "/topic/humidity"
extern volatile bool mqtt_restart_requested;

void app_main(void)
{
    ESP_LOGI("MAIN", "[APP] Startup..");
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    float humidity = 0.0f;
    float temperature = 0.0f;
    esp_err_t err = ESP_FAIL;

    mqtt_app_start();

    char display_str[32];
    esp_lcd_panel_handle_t panel_handle = NULL;
    oled_init(&panel_handle);

    while (1)
    {
        err = read_dht_sensor(&humidity, &temperature);
        if (err != ESP_OK)
        {
            snprintf(display_str, sizeof(display_str), "DHT Error:\n%s", esp_err_to_name(err));
        }
        else
        {
            snprintf(display_str, sizeof(display_str), "Humidity: %.2f%%\nTemp: %.2fC", humidity, temperature);
            char humidity_str[16];
            char temperature_str[16];
            snprintf(temperature_str, sizeof(temperature_str), "%.2f", temperature);
            snprintf(humidity_str, sizeof(humidity_str), "%.2f", humidity);
            esp_mqtt_client_publish(client, TEMPERATURE_TOPIC, temperature_str, 0, 0, 0);
            esp_mqtt_client_publish(client, HUMIDITY_TOPIC, humidity_str, 0, 0, 0);
        }
        oled_draw_text(panel_handle, display_str);

        if (mqtt_restart_requested)
        {
            mqtt_restart_requested = false;
            esp_mqtt_client_stop(client);
            esp_mqtt_client_destroy(client);
            mqtt_app_start();
        }
        sleep(5);
    }
}