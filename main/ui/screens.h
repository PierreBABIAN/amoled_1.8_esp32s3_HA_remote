#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *light;
    lv_obj_t *light_1;
    lv_obj_t *clock_label;
    lv_obj_t *prev;
    lv_obj_t *next;
    lv_obj_t *temp_label;
    lv_obj_t *obj0;
    lv_obj_t *prev_1;
    lv_obj_t *next_1;
    lv_obj_t *hue;
    lv_obj_t *slid_lumi;
    lv_obj_t *prev_2;
    lv_obj_t *next_2;
    lv_obj_t *temp;
    lv_obj_t *co2;
    lv_obj_t *lumi;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_LIGHT = 2,
    SCREEN_ID_LIGHT_1 = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_light();
void tick_screen_light();

void create_screen_light_1();
void tick_screen_light_1();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/