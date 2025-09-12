cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_ai_pro_controller)

pico_sdk_init()

add_executable(pico_ai_pro_controller
    main.c
    usb_descriptors.c
    model_data.h
    tflm_micro_interpreter.c
    tflm_ops.c
)

target_include_directories(pico_ai_pro_controller PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pico_ai_pro_controller pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(pico_ai_pro_controller)
