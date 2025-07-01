#include "mqtt_app.h"
#include "esp_log.h"
#include <string.h>
#include "esp_ota_ops.h"
#include "esp_partition.h"
#include "credentials.h"

#define TEMPERATURE_TOPIC "/topic/temperature"
#define HUMIDITY_TOPIC "/topic/humidity"

static const char *TAG = "mqtts_example";
static bool using_fallback_broker = false;
bool mqtt_connected = false;
volatile bool mqtt_restart_requested = false;

esp_mqtt_client_handle_t client = NULL;

extern const uint8_t mqtt_eclipseprojects_io_pem_start[] asm("_binary_mqtt_eclipseprojects_io_pem_start");

extern const uint8_t mqtt_eclipseprojects_io_pem_end[] asm("_binary_mqtt_eclipseprojects_io_pem_end");

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        esp_mqtt_client_subscribe(client, TEMPERATURE_TOPIC, 0);
        esp_mqtt_client_subscribe(client, HUMIDITY_TOPIC, 0);
        mqtt_connected = true;
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR or DISCONNECTED");
        if (!using_fallback_broker)
        {
            using_fallback_broker = true;
            ESP_LOGI(TAG, "Switching to fallback broker...");
            mqtt_restart_requested = true;
            esp_mqtt_client_reconnect(client);
        }
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA, topic=%.*s, data=%.*s", event->topic_len, event->topic, event->data_len, event->data);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {0};
    if (!using_fallback_broker)
    {
        mqtt_cfg.broker.address.uri = PRIMARY_BROKER_URI;
        mqtt_cfg.broker.address.port = PRIMARY_BROKER_PORT;
        mqtt_cfg.broker.verification.certificate = (const char *)mqtt_eclipseprojects_io_pem_start;
        // mqtt_cfg.credentials.username = BROKER_USER;
        // mqtt_cfg.credentials.authentication.password = BROKER_PASSWORD;
    }
    else
    {
        mqtt_cfg.broker.address.uri = FALLBACK_BROKER_URI;
        mqtt_cfg.broker.address.port = FALLBACK_BROKER_PORT;
        //    mqtt_cfg.broker.verification.certificate = NULL;
    }

    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
    // ESP_LOGI(TAG, "MQTT client started with broker %s:%d", mqtt_cfg.broker.address.uri, mqtt_cfg.broker.address.port);
}
