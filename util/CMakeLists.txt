set(TARGET util)

add_library(padding STATIC padding.cpp)

target_include_directories(padding PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(padding PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})









