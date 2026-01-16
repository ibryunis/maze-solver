aux_source_directory(. DIR_Pico_Servo_Driver_SRCS)

include_directories(../config)

add_library(devices ${DIR_Pico_Servo_Driver_SRCS})
target_link_libraries(devices PUBLIC config)