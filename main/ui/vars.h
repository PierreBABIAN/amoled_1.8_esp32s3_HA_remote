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
    FLOW_GLOBAL_VARIABLE_CLOCK = 0,
    FLOW_GLOBAL_VARIABLE_TEMP = 1,
    FLOW_GLOBAL_VARIABLE_LIGHT_LUMI = 2,
    FLOW_GLOBAL_VARIABLE_LIGHT_ON = 3,
    FLOW_GLOBAL_VARIABLE_LIGHT_COLOR = 4
};

// Native global variables

extern const char *get_var_clock();
extern void set_var_clock(const char *value);
extern const char *get_var_temp();
extern void set_var_temp(const char *value);
extern int32_t get_var_light_lumi();
extern void set_var_light_lumi(int32_t value);
extern int32_t get_var_light_on();
extern void set_var_light_on(int32_t value);
extern int32_t get_var_light_color();
extern void set_var_light_color(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/