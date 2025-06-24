#ifndef DHT_APP_H
#define DHT_APP_H

#include "esp_err.h"

esp_err_t read_dht_sensor(float *humidity, float *temperature);

#endif // DHT_APP_H