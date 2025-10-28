cmake_minimum_required(VERSION 3.10)
project(Laba_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files directly to the executable
add_executable(Laba_4
    main.cpp
    Human.cpp
    Prepod.cpp
    Member_of_commision.cpp
    Prepod_from_commision.cpp
    BinTree.cpp
    BinLeaf.cpp
)
