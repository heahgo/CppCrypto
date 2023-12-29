set(TARGET1 aes)
set(TARGET2 aes_table)

add_library(${TARGET1} STATIC aes.cpp aes_core.cpp aes_ecb.cpp)
add_library(${TARGET2} STATIC table.cpp aes_table.cpp table_ecb.cpp aes_core.cpp)

target_include_directories(${TARGET1} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${TARGET2} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(${TARGET1} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties(${TARGET2} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})