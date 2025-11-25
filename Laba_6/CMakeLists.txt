cmake_minimum_required(VERSION 3.10)
project(Laba_6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all source files
set(SOURCES
    main.cpp
    Human.cpp
    Member_of_commision.cpp
    Prepod_from_commision.cpp
    Prepod.cpp
    InputValidator.cpp
)

# Create single executable with all sources
add_executable(Laba_6 ${SOURCES})
