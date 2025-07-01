# Proyecto: MQTT Sensors con ESP-IDF

Este proyecto es un ejemplo de aplicación IoT usando el framework **ESP-IDF** de Espressif. El sistema lee datos de un sensor de temperatura y humedad **DHT22**, los muestra en una pantalla OLED **SH1106** y los publica a un broker usando el protocolo **MQTT** con **certificados TLS** para comunicación segura.

## Componentes utilizados

- **ESP32**: Microcontrolador principal.
- **Sensor DHT22**: Sensor digital de temperatura y humedad.
- **Pantalla OLED SH1106**: Pantalla gráfica monocromática de 128x64 píxeles, conectada por I2C.
- **Protocolo MQTT**: Para la transmisión de datos a un servidor/broker MQTT.
- **TLS/SSL**: Seguridad en la comunicación MQTT mediante certificados digitales.
- **LVGL**: (Opcional) Librería gráfica para interfaces de usuario en la pantalla OLED.
- **ESP-IDF**: Framework oficial de Espressif para desarrollo en ESP32.

## Estructura del proyecto

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── main.c
│   ├── oled_display.c
│   ├── oled_display.h
│   ├── mqtt_app.c
│   ├── mqtt_app.h
│   ├── dht_app.c
│   ├── dht_app.h
│   └── ui/ (código generado para la interfaz gráfica, si se usa LVGL)
└── README.md
```

## Descripción general

- El **DHT22** se conecta a un pin GPIO y se lee periódicamente.
- Los datos se muestran en la pantalla **OLED SH1106** usando I2C.
- Los valores de temperatura y humedad se publican en tópicos MQTT usando una conexión segura (TLS).
- El código está organizado en módulos para facilitar el mantenimiento y la extensión.

## Notas

- Para usar MQTT con TLS, asegúrate de configurar correctamente los certificados en el código y en el broker.
- La pantalla SH1106 requiere una inicialización especial y el uso de una librería compatible (por ejemplo, `esp_lcd_panel_sh1106`).
- El framework **ESP-IDF** permite una integración sencilla de todos estos componentes y protocolos.

## Ejemplo para agregar credenciales en archivo credentials.h

#define PRIMARY_BROKER_URI "mqtts://111.22.331.175"
#define PRIMARY_BROKER_PORT 8883
#define BROKER_USER "IOT-jfjf"
#define BROKER_PASSWORD "dsjiafkjg"

#define FALLBACK_BROKER_URI "mqtt://broker.hivemq.com"
#define FALLBACK_BROKER_PORT 1883

---
