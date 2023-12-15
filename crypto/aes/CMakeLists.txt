set(TARGET aes)

sub1
add_library(aes OBJECT aes.cpp)
sub2
add_library(aes_core OBJECT aes_core.cpp)

add_library(aes_ecb OBJECT aes_ecb.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include)




