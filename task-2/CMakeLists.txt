##################### PROJECT INFO #####################
cmake_minimum_required(VERSION 3.14)
project(GOL LANGUAGES CXX)
set(PROJECT_NAME GameOfLife)

################### COMPLIER OPTIONS ###################
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror 
        -Wall -Wextra -Wpedantic
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()
add_definitions(
    -DDEFAULT_INPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/sources/game_sources/input/"
    -DDEFAULT_OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/sources/game_sources/output/"
)
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

#################### EXTRA OPTIONS ####################
option(TESTING "Включить модульное тестирование" ON)
option(COVERAGE "Включить измерение покрытия кода тестами" OFF)

####################### SOURCES #######################
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/src
)
file(GLOB ALL_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/sources/include/*.hpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/sources/src/*.cpp"
)
add_library(Sources ${ALL_SRCS})

######################## MAIN ########################
add_executable(main 
    main.cpp
)
target_link_libraries(main Sources)

####################### TESTS ########################
if (TESTING)
    add_subdirectory(test)
endif()
