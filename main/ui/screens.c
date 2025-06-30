#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main()
{
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 128, 128);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xff207eaf), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff080303), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff202b46), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // panel_humedad
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_humedad = obj;
            lv_obj_set_pos(obj, 4, 32);
            lv_obj_set_size(obj, LV_PCT(94), LV_PCT(34));
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_post(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 41, -25);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_hum);
                    lv_image_set_scale(obj, 120);
                }
                {
                    // temperatura_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperatura_1 = obj;
                    lv_obj_set_pos(obj, 0, -1);
                    lv_obj_set_size(obj, LV_PCT(50), LV_PCT(100));
                    lv_obj_set_style_text_font(obj, LV_FONT_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0af9ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // panel_temperatura
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_temperatura = obj;
            lv_obj_set_pos(obj, 4, 81);
            lv_obj_set_size(obj, LV_PCT(94), LV_PCT(34));
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_post(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 41, -25);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_temp_icon);
                    lv_image_set_scale(obj, 140);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffaffdff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_temperatura
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temperatura = obj;
                    lv_obj_set_pos(obj, 0, -1);
                    lv_obj_set_size(obj, LV_PCT(50), LV_PCT(100));
                    lv_obj_set_style_text_font(obj, LV_FONT_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff0af9ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 4, 5);
            lv_obj_set_size(obj, LV_PCT(94), 22);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, -6, -36);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_broker);
                    lv_image_set_scale(obj, 70);
                }
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, -29, -37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_wifi);
                    lv_image_set_scale(obj, 70);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                }
            }
        }
    }

    tick_screen_main();
}

void tick_screen_main()
{
    {
        static char hum_str[16];
        float hum_val = get_var_humedad();
        snprintf(hum_str, sizeof(hum_str), "%.2f", hum_val);
        const char *cur_val = lv_label_get_text(objects.temperatura_1);
        if (strcmp(hum_str, cur_val) != 0)
        {
            tick_value_change_obj = objects.temperatura_1;
            lv_label_set_text(objects.temperatura_1, hum_str);
            tick_value_change_obj = NULL;
        }
    }
    {
        static char temp_str[16];
        float temp_val = get_var_temperatura();
        snprintf(temp_str, sizeof(temp_str), "%.2f", temp_val);
        const char *cur_val = lv_label_get_text(objects.label_temperatura);
        if (strcmp(temp_str, cur_val) != 0)
        {
            tick_value_change_obj = objects.label_temperatura;
            lv_label_set_text(objects.label_temperatura, temp_str);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_broker();
        bool cur_val = lv_obj_has_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val)
        {
            tick_value_change_obj = objects.obj2;
            if (new_val)
                lv_obj_add_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
            else
                lv_obj_clear_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_wifi();
        bool cur_val = lv_obj_has_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val)
        {
            tick_value_change_obj = objects.obj3;
            if (new_val)
                lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            else
                lv_obj_clear_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index)
{
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId)
{
    tick_screen_funcs[screenId - 1]();
}

void create_screens()
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_main();
}
