
cmake_minimum_required(VERSION 3.10)
project(Laba_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(BinTree STATIC BinTree.cpp)
add_library(BinLeaf STATIC BinLeaf.cpp)

add_executable(Laba_4 main.cpp)

target_link_libraries(Laba_4 BinTree)
target_link_libraries(Laba_4 BinLeaf)
