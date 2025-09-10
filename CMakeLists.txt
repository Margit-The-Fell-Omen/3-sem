
cmake_minimum_required(VERSION 3.10)
project(Laba_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(my_string STATIC my_string.cpp)

add_executable(Laba_1 main.cpp)

target_link_libraries(Laba_1 my_string)

