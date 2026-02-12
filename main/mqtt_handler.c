#include <stdio.h>
#include "mqtt_client.h"
#include "mqtt_handler.h"
#include "esp_log.h"
#include "cJSON.h"

#define TAG     "MQTT"

struct mqtt_context mqtt_ctx;

static esp_mqtt_client_handle_t client = NULL;

struct mqtt_context *get_mqtt_ctx(void)
{
    return &mqtt_ctx;
}

void mqtt_data_handler(const char *mqtt_payload)
{
    // Parse le JSON
    cJSON *root = cJSON_Parse(mqtt_payload);
    if (!root) {
        printf("Erreur de parsing JSON\n");
        return;
    }

    // Accède à "statistics"
    cJSON *statistics = cJSON_GetObjectItem(root, "statistics");
    if (!statistics) {
        printf("Champ 'statistics' manquant\n");
        cJSON_Delete(root);
        return;
    }

    // Accède à "sensor.temp"
    cJSON *sensor_array = cJSON_GetObjectItem(statistics, "sensor.temp");
    if (!sensor_array || !cJSON_IsArray(sensor_array)) {
        printf("Champ 'sensor.temp' manquant ou pas un array\n");
        cJSON_Delete(root);
        return;
    }

    // Parcourt le tableau
    int count = cJSON_GetArraySize(sensor_array);
    for (int i = 0; (i < count) && (i < SIZE_STR_DATA); i++) {
        cJSON *entry = cJSON_GetArrayItem(sensor_array, i);
        if (entry) {
            cJSON *mean_item = cJSON_GetObjectItem(entry, "mean");
            if (mean_item && cJSON_IsNumber(mean_item)) {
                mqtt_ctx.temp_arr[i] = mean_item->valuedouble;
                // TODO : stocker ou traiter ici
            }
        }
    }

    cJSON_Delete(root); // Libère la mémoire
}

void mqtt_publish_int(int topic, uint32_t val) {
    char buffer[16];
    sprintf(buffer, "%d", val);
    switch(topic) {
        case TOPIC_LIGHT:
            mqtt_ctx.light_lumi_cmd = (int)val;
            esp_mqtt_client_publish(client, TOPIC_LIGHT_STR, buffer, 0, 1, 0);
            break;
        case TOPIC_COLOR:
            mqtt_ctx.light_color = (int)val;
            esp_mqtt_client_publish(client, TOPIC_COLOR_STR, buffer, 0, 1, 0);
            break;
        case TOPIC_LON:
            mqtt_ctx.light_on = (int)val;
            esp_mqtt_client_publish(client, TOPIC_LON_STR, buffer, 0, 1, 0);
            break;
        case TOPIC_AUTO_BRIGHT:
            mqtt_ctx.light_auto_bright = (int)val;
            esp_mqtt_client_publish(client, TOPIC_AUTO_BRIGHT_STR, buffer, 0, 1, 0);
            break;

    }
    ESP_LOGI(TAG, "Published message");
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "Connected to broker, subscribing...");
            esp_mqtt_client_subscribe(client, SUB_TOPIC_TEMP, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_LUMI, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_LUMI_CMD, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_COLOR, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_LON, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_AUTO_BRIGHT, 0);
            esp_mqtt_client_subscribe(client, SUB_TOPIC_TEMP_ARR, 0);
            break;

        case MQTT_EVENT_DATA:
            if (!strncmp(event->topic, SUB_TOPIC_TEMP, event->topic_len))
            {
                ESP_LOGI(TAG, "SUB_TOPIC_TEMP");
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(mqtt_ctx.temp_str, '\0', SIZE_STR_DATA);
                snprintf(mqtt_ctx.temp_str, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                for (uint16_t i = VAL_HISTO_SIZE - 2; i > 0; i--)
                {
                    mqtt_ctx.temp_arr[i + 1] = (uint32_t)mqtt_ctx.temp_arr[i];
                }
                mqtt_ctx.temp_arr[0] = atof(mqtt_ctx.temp_str);
                //objects.temp
                mqtt_ctx.update_req = 1;
                
            }
            else if (!strncmp(event->topic, SUB_TOPIC_LUMI, event->topic_len))
            {
                ESP_LOGI(TAG, "SUB_TOPIC_LUMI");
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(mqtt_ctx.lumi_str, '\0', SIZE_STR_DATA);
                snprintf(mqtt_ctx.lumi_str, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                for (uint16_t i = VAL_HISTO_SIZE - 2; i > 0; i--)
                {
                    mqtt_ctx.light_lumi_arr[i + 1] = mqtt_ctx.light_lumi_arr[i];
                }
                mqtt_ctx.light_lumi_arr[0] = atoi(mqtt_ctx.lumi_str);
                mqtt_ctx.update_req = 1;
            }
            else if (!strncmp(event->topic, SUB_TOPIC_LUMI_CMD, event->topic_len))
            {
                char light_lumi_buf[SIZE_STR_DATA];
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(mqtt_ctx.lumi_str, '\0', SIZE_STR_DATA);
                snprintf(light_lumi_buf, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                mqtt_ctx.light_lumi_cmd = atoi(light_lumi_buf);
                mqtt_ctx.update_req = 1;
            }
            else if (!strncmp(event->topic, SUB_TOPIC_COLOR, event->topic_len))
            {
                char light_color_buf[SIZE_STR_DATA];
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(light_color_buf, '\0', SIZE_STR_DATA);
                snprintf(light_color_buf, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                mqtt_ctx.light_color = atoi(light_color_buf);
                mqtt_ctx.update_req = 1;
            }
            else if (!strncmp(event->topic, SUB_TOPIC_LON, event->topic_len))
            {
                char light_on_buf[SIZE_STR_DATA];
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(light_on_buf, '\0', SIZE_STR_DATA);
                snprintf(light_on_buf, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                mqtt_ctx.light_on = atoi(light_on_buf);
                mqtt_ctx.update_req = 1;
            }
            else if (!strncmp(event->topic, SUB_TOPIC_AUTO_BRIGHT, event->topic_len))
            {
                char light_auto_bright_buf[SIZE_STR_DATA];
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
                        memset(light_auto_bright_buf, '\0', SIZE_STR_DATA);
                snprintf(light_auto_bright_buf, event->data_len + 4, "%.*s°C", event->data_len, event->data);
                mqtt_ctx.light_auto_bright = atoi(light_auto_bright_buf);
                mqtt_ctx.update_req = 1;
            }
            else if (!strncmp(event->topic, SUB_TOPIC_TEMP_ARR, event->topic_len))
            {
                char payload[event->data_len + 1];
                memcpy(payload, event->data, event->data_len);
                payload[event->data_len] = '\0';
                mqtt_data_handler(payload);
                ESP_LOGI(TAG, "Received on topic %.*s: %.*s",
                        event->topic_len, event->topic,
                        event->data_len, event->data);
            }
            break;

        default:
            break;
    }
}

void mqtt_app_start(void) {

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER_URI,
        .credentials.username = "Dumuys",
        .credentials.authentication.password = "Vert4green",
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}