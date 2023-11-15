set(TARGET aes)

add_library(${TARGET} STATIC ${TARGET}.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include/${TARGET})
target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include/util)

target_compile_options(${TARGET} PRIVATE -Wall -Werror)

add_subdirectory(aes)
add_subdirectory(util)