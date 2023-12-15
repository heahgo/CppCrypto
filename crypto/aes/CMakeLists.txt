set(TARGET aes)

add_library(aes STATIC aes.cpp aes_core.cpp aes_ecb.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(${TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})