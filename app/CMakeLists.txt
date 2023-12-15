set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/app/bin)
set(TARGET aes_test)

add_executable(${TARGET} aes_test.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(aes_test ${CMAKE_SOURCE_DIR}/lib/libaes.a ${CMAKE_SOURCE_DIR}/lib/libpadding.a)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})