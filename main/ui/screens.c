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

static void event_handler_cb_main_main(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_light_on(value);
        }
    }
}

static void event_handler_unchecked_cb_main_light_sw(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (!lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_light_off(e);
    }
}

static void event_handler_checked_cb_main_light_sw(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_light_on(e);
    }
}

static void event_handler_cb_main_light_sw(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_light_on(value);
        }
    }
}

static void event_handler_cb_light_hue(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_light_color(value);
        }
    }
}

static void event_handler_cb_light_slid_lumi(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_light_lumi(value);
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 368, 448);
    lv_obj_add_event_cb(obj, event_handler_cb_main_main, LV_EVENT_ALL, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // clock_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_label = obj;
            lv_obj_set_pos(obj, 0, -27);
            lv_obj_set_size(obj, 214, 54);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff242424), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // prev
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.prev = obj;
            lv_obj_set_pos(obj, 19, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_prev, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
        {
            // next
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.next = obj;
            lv_obj_set_pos(obj, 199, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_next, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
        {
            // temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_label = obj;
            lv_obj_set_pos(obj, 7, -163);
            lv_obj_set_size(obj, 107, 31);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff242424), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // light_sw
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.light_sw = obj;
            lv_obj_set_pos(obj, 129, 290);
            lv_obj_set_size(obj, 101, 59);
            lv_obj_add_event_cb(obj, event_handler_unchecked_cb_main_light_sw, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_checked_cb_main_light_sw, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_light_sw, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_INDICATOR | LV_STATE_CHECKED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_INDICATOR | LV_STATE_PRESSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_KNOB | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        bool new_val = get_var_light_on();
        bool cur_val = lv_obj_has_state(objects.main, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main;
            if (new_val) lv_obj_add_state(objects.main, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.main, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_light_on();
        bool cur_val = lv_obj_has_flag(objects.main, LV_OBJ_FLAG_CLICKABLE);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main;
            if (new_val) lv_obj_add_flag(objects.main, LV_OBJ_FLAG_CLICKABLE);
            else lv_obj_clear_flag(objects.main, LV_OBJ_FLAG_CLICKABLE);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_clock();
        const char *cur_val = lv_label_get_text(objects.clock_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.clock_label;
            lv_label_set_text(objects.clock_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_temp();
        const char *cur_val = lv_label_get_text(objects.temp_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temp_label;
            lv_label_set_text(objects.temp_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_light_on();
        bool cur_val = lv_obj_has_state(objects.light_sw, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.light_sw;
            if (new_val) lv_obj_add_state(objects.light_sw, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.light_sw, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_light() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.light = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 368, 448);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // hue
            lv_obj_t *obj = lv_colorwheel_create(parent_obj, false);
            objects.hue = obj;
            lv_obj_set_pos(obj, 62, 102);
            lv_obj_set_size(obj, 244, 244);
            lv_obj_add_event_cb(obj, event_handler_cb_light_hue, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // slid_lumi
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slid_lumi = obj;
            lv_obj_set_pos(obj, 53, 33);
            lv_obj_set_size(obj, 262, 27);
            lv_obj_add_event_cb(obj, event_handler_cb_light_slid_lumi, LV_EVENT_ALL, 0);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff8a8a8a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffb4b4b4), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc9c9c9), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // prev_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.prev_1 = obj;
            lv_obj_set_pos(obj, 19, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_prev, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
        {
            // next_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.next_1 = obj;
            lv_obj_set_pos(obj, 199, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_next, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_light();
}

void tick_screen_light() {
    {
        bool new_val = get_var_light_color();
        bool cur_val = lv_obj_has_state(objects.hue, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.hue;
            if (new_val) lv_obj_add_state(objects.hue, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.hue, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_light_lumi();
        int32_t cur_val = lv_slider_get_value(objects.slid_lumi);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.slid_lumi;
            lv_slider_set_value(objects.slid_lumi, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_light_1() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.light_1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 368, 448);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temp
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.temp = obj;
            lv_obj_set_pos(obj, 19, 20);
            lv_obj_set_size(obj, 330, 100);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // co2
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.co2 = obj;
            lv_obj_set_pos(obj, 19, 140);
            lv_obj_set_size(obj, 330, 100);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // lumi
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.lumi = obj;
            lv_obj_set_pos(obj, 19, 260);
            lv_obj_set_size(obj, 330, 100);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_line_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff2f3237), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // prev_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.prev_2 = obj;
            lv_obj_set_pos(obj, 19, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_prev, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
        {
            // next_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.next_2 = obj;
            lv_obj_set_pos(obj, 199, 401);
            lv_obj_set_size(obj, 150, 35);
            lv_obj_add_event_cb(obj, action_next, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_light_1();
}

void tick_screen_light_1() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_light,
    tick_screen_light_1,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_light();
    create_screen_light_1();
}
