
cmake_minimum_required(VERSION 3.10)
project(Laba_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Human STATIC Human.cpp)
add_library(Prepod_from_commision STATIC Prepod_from_commision.cpp)
add_library(Member_of_commision STATIC Member_of_commision.cpp)
add_library(Prepod STATIC Prepod.cpp)

add_executable(Laba_3 main.cpp)

target_link_libraries(Laba_3 Human)
target_link_libraries(Laba_3 Prepod_from_commision)
target_link_libraries(Laba_3 Member_of_commision)
target_link_libraries(Laba_3 Prepod)

