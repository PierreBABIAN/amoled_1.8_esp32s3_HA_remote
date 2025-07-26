#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_next(lv_event_t * e);
extern void action_prev(lv_event_t * e);
extern void action_test(lv_event_t * e);
extern void action_light_on(lv_event_t * e);
extern void action_light_off(lv_event_t * e);
extern void action_test_color(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/