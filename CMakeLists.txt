cmake_minimum_required(VERSION 3.24)
project(API C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)
add_executable(API main.c)
target_link_libraries(API curl)
include_directories("Curl/curl-7.88.1_2-win64-mingw/include")
link_directories("Curl/curl-7.88.1_2-win64-mingw/include/curl")