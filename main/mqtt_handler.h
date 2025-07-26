#ifndef MQTT_HANDLER_MINI_DISP
#define MQTT_HANDLER_MINI_DISP

#include <stdint.h>
#include <stdbool.h>

#define BROKER_URI "mqtt://homeassistant.local"
#define SUB_TOPIC_TEMP "homeassistant/sensor/test/temperature"
#define SUB_TOPIC_LUMI "homeassistant/sensor/test/lumi"
#define SUB_TOPIC_LUMI_CMD "homeassistant/sensor/test/lumi_cmd"
#define SUB_TOPIC_COLOR "homeassistant/sensor/test/color"
#define SUB_TOPIC_LON "homeassistant/sensor/test/lon"
#define PUB_TOPIC "esp32s3/out"

#define TOPIC_LON_STR       "test/lon"
#define TOPIC_COLOR_STR       "test/color"
#define TOPIC_LIGHT_STR       "test/light"

#define SIZE_STR_DATA       32
#define VAL_HISTO_SIZE      32

enum topics_used {
    TOPIC_LIGHT,
    TOPIC_COLOR,
    TOPIC_LON
};

struct mqtt_context {
    const char time_str[SIZE_STR_DATA];
    const char temp_str[SIZE_STR_DATA];
    const char lumi_str[SIZE_STR_DATA];
    int light_lumi_arr[VAL_HISTO_SIZE];
    float temp_arr[VAL_HISTO_SIZE];
    int light_lumi_cmd;
    int light_color;
    int light_on;
    int update_req;
};

struct mqtt_context *get_mqtt_ctx(void);
void mqtt_publish_int(int topic, uint32_t val);
void mqtt_app_start(void);

#endif //MQTT_HANDLER_MINI_DISP