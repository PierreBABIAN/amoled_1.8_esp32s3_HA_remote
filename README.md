

# Amoled 1.8 ESP32s3 application

## Hardware Required

* An ESP32s3 amoled 1.8 https://www.waveshare.com/esp32-s3-touch-amoled-1.8.htm
* An USB cable for power supply and programming
  
# Intro

This is my attempt to make my board work, for now the code is ugly.
Is using on board components (for now) :
       - Disp(RAM)/touch
       - LVGL
       - RTC
       - Wifi
       - MQTT

The lvgl UI is created throuh EEZ studio.

# MQTT

#define BROKER_URI "mqtt://homeassistant.local"

Topics that the device is listening :
#define SUB_TOPIC_TEMP "homeassistant/sensor/test/temperature"
#define SUB_TOPIC_LUMI "homeassistant/sensor/test/lumi"
#define SUB_TOPIC_LUMI_CMD "homeassistant/sensor/test/lumi_cmd"
#define SUB_TOPIC_COLOR "homeassistant/sensor/test/color"
#define SUB_TOPIC_LON "homeassistant/sensor/test/lon"

topics that the device is righting on :
#define TOPIC_LON_STR       "test/lon"
#define TOPIC_COLOR_STR       "test/color"
#define TOPIC_LIGHT_STR       "test/light"

```

```
