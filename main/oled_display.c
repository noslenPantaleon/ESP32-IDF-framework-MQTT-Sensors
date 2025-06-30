#include "oled_display.h"
#include <string.h>
#include "esp_lcd_panel_sh1106.h"
#include "esp_lcd_io_i2c.h"
#include "driver/i2c_master.h"

#define SH1106_WIDTH 128
#define SH1106_HEIGHT 64
#define SH1106_SCREEN_SIZE (SH1106_WIDTH * SH1106_HEIGHT / 8)
#define I2C_SDA_GPIO GPIO_NUM_21
#define I2C_SCL_GPIO GPIO_NUM_22
#define I2C_HOST 0

const uint8_t sh1106_font8x8_basic[96][8] = {
    // ASCII 32 (space) to 127 (~)
    // Each character is 8 bytes (8x8 pixels)
    // You can find a full font at: https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
    {0, 0, 0, 0, 0, 0, 0, 0},                         // space
    {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00}, // !
    {0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00}, // "
    {0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, 0x00, 0x00}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, 0x00, 0x00}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62, 0x00, 0x00, 0x00}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x00, 0x00}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, 0x00, 0x00}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00, 0x00}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00, 0x00}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46, 0x00, 0x00, 0x00}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31, 0x00, 0x00, 0x00}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00, 0x00}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00, 0x00}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00, 0x00}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00, 0x00}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00, 0x00}, // 9
};

void oled_init(esp_lcd_panel_handle_t *panel_handle)
{
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_HOST,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false,
        },
    };
    i2c_master_bus_handle_t i2c_bus_handle = NULL;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus_handle));

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = ESP_SH1106_DEFAULT_IO_CONFIG;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus_handle, &io_config, &io_handle));
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .data_endian = LCD_RGB_DATA_ENDIAN_LITTLE,
        .bits_per_pixel = SH1106_PIXELS_PER_BYTE / 8,
        .flags = {
            .reset_active_high = false,
        },
        .vendor_config = NULL,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_sh1106(io_handle, &panel_config, panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(*panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(*panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(*panel_handle, true));
}

void oled_draw_text(esp_lcd_panel_handle_t panel_handle, const char *text)
{
    uint8_t buffer_data[SH1106_SCREEN_SIZE];
    memset(buffer_data, 0, sizeof(buffer_data));

    // Calculate text width and height in pixels
    int lines = 1, max_line_len = 0, curr_line_len = 0;
    for (const char *p = text; *p; ++p)
    {
        if (*p == '\n')
        {
            if (curr_line_len > max_line_len)
                max_line_len = curr_line_len;
            curr_line_len = 0;
            lines++;
        }
        else
        {
            curr_line_len++;
        }
    }
    if (curr_line_len > max_line_len)
        max_line_len = curr_line_len;

    int text_width = max_line_len * 8;
    int text_height = lines * 8;

    int start_x = (SH1106_WIDTH - text_width) / 2;
    int start_y = (SH1106_HEIGHT - text_height) / 2;

    int x = start_x, y = start_y;
    for (const char *p = text; *p && y < SH1106_HEIGHT; ++p)
    {
        if (*p >= 32 && *p <= 127)
        {
            const uint8_t *glyph = sh1106_font8x8_basic[*p - 32];
            for (int row = 0; row < 8; ++row)
            {
                int byte_index = (x / 8) + (y / 8) * (SH1106_WIDTH / 8) + row * (SH1106_WIDTH / 8);
                if (byte_index < SH1106_SCREEN_SIZE)
                {
                    buffer_data[(y / 8) * SH1106_WIDTH + x + row] = glyph[row];
                }
            }
            x += 8;
            if (x + 8 > SH1106_WIDTH)
            {
                x = start_x;
                y += 8;
            }
        }
        else if (*p == '\n')
        {
            x = start_x;
            y += 8;
        }
    }
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, SH1106_WIDTH, SH1106_HEIGHT, buffer_data));
}