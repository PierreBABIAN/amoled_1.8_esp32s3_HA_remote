idf_component_register(
    SRCS "mqtt_handler.c" "example_qspi_with_ram.c" "ui/ui.c" "ui/images.c" "ui/styles.c" "ui/screens.c"
    INCLUDE_DIRS ".")


set_source_files_properties(
    ${LV_DEMOS_SOURCES}
    PROPERTIES COMPILE_OPTIONS
    -DLV_LVGL_H_INCLUDE_SIMPLE)
