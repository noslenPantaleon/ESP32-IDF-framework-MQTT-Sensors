#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_TEMPERATURA = 0,
    FLOW_GLOBAL_VARIABLE_HUMEDAD = 1,
    FLOW_GLOBAL_VARIABLE_WIFI = 2,
    FLOW_GLOBAL_VARIABLE_BROKER = 3
};

// Native global variables

extern float get_var_temperatura();
extern void set_var_temperatura(float value);
extern float get_var_humedad();
extern void set_var_humedad(float value);
extern bool get_var_wifi();
extern void set_var_wifi(bool value);
extern bool get_var_broker();
extern void set_var_broker(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/