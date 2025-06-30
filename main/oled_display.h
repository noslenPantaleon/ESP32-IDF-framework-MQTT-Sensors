#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include "esp_lcd_panel_ops.h"

void oled_init(esp_lcd_panel_handle_t *panel_handle);
void oled_draw_text(esp_lcd_panel_handle_t panel_handle, const char *text);

#endif // OLED_DISPLAY_H