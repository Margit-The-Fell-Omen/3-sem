cmake_minimum_required(VERSION 3.10)
project(Laba_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all source files
set(SOURCES
    main.cpp
    Human.cpp
    Prepod.cpp
    Member_of_commision.cpp
    Prepod_from_commision.cpp
    BinTree.cpp
    BinLeaf.cpp
    functions.cpp
)

# Create single executable with all sources
add_executable(Laba_4 ${SOURCES})
