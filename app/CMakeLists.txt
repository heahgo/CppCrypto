set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)

# add_executable(${OUTPUT_DIR} aes_test.cpp)
target_include_directories(${CMAKE_SOURCE_DIR} PRIVATE include)
target_link_libraries(aes_test ${CMAKE_SOURCE_DIR}/aes)