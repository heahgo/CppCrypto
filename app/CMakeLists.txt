set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/app/bin)
set(TARGET1 aes_test)
set(TARGET2 table_test)
set(TARGET3 speed)

set(variable FILEPATH ${CMAKE_SOURCE_DIR}/app)
add_executable(${TARGET1} aes_test.cpp)
add_executable(${TARGET2} table_test.cpp)
add_executable(${TARGET3} speed.cpp)

target_include_directories(${TARGET1} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${TARGET2} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${TARGET3} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${TARGET1} PUBLIC ${CMAKE_SOURCE_DIR}/app)
target_include_directories(${TARGET2} PUBLIC ${CMAKE_SOURCE_DIR}/app)
target_include_directories(${TARGET3} PUBLIC ${CMAKE_SOURCE_DIR}/app)

target_link_libraries(${TARGET1} ${CMAKE_SOURCE_DIR}/lib/libaes.a ${CMAKE_SOURCE_DIR}/lib/libpadding.a)
target_link_libraries(${TARGET2} ${CMAKE_SOURCE_DIR}/lib/libaes_table.a ${CMAKE_SOURCE_DIR}/lib/libpadding.a)
target_link_libraries(${TARGET3} ${CMAKE_SOURCE_DIR}/lib/libaes.a ${CMAKE_SOURCE_DIR}/lib/libaes_table.a ${CMAKE_SOURCE_DIR}/lib/libpadding.a)

set_target_properties(${TARGET1} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties(${TARGET2} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_target_properties(${TARGET3} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})