aux_source_directory(. DIR_Pico_Objects_SRCS)

include_directories(../devices ../config)

add_library(objects ${DIR_Pico_Objects_SRCS})
target_link_libraries(objects PUBLIC devices config pico_stdlib pico_multicore)