#include "dht_app.h"
#include "dht.h"

#define PIN_DHT22 4

esp_err_t read_dht_sensor(float *humidity, float *temperature)
{
    return dht_read_float_data(DHT_TYPE_DHT22, PIN_DHT22, humidity, temperature);
}