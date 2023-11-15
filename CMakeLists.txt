CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)

PROJECT(
    CppCrypto
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Implement Crypto Library in Cpp"
    )

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/app)

add_subdirectory(crypto)
add_subdirectory(include)
add_subdirectory(util)