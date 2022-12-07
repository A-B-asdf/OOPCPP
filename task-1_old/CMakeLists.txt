###################################################################################################
##
##      Информация о проекте
##
###################################################################################################

cmake_minimum_required(VERSION 3.20)
project(BigInt LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

###################################################################################################
##
##      Опции проекта
##
###################################################################################################

if (IS_SUBPROJECT AND NOT DEFINED BIGINT_TESTING)
    message(STATUS "BigInt не тестируется в режиме подмодуля")
    set(BIGINT_TESTING OFF)
endif()

option(BIGINT_TESTING "Включить модульное тестирование" ON)
option(BIGINT_COVERAGE "Включить измерение покрытия кода тестами" OFF)

###################################################################################################
##
##      Опции компиляции
##
###################################################################################################

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

###################################################################################################
##
##      Заголовочная библиотека
##
###################################################################################################

add_library(bigint_headers INTERFACE)
target_include_directories(bigint_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(bigint_headers INTERFACE cxx_std_17)

add_library(BigInt::headers ALIAS bigint_headers)

###################################################################################################
##
##      Компилируемая библиотека
##
###################################################################################################

add_library(bigint_library src/bigint/source.cpp)
target_link_libraries(bigint_library PUBLIC bigint_headers)

add_library(BigInt::library ALIAS bigint_library)

###################################################################################################
##
##      Установка
##
###################################################################################################

install(DIRECTORY include/bigint DESTINATION include)

install(TARGETS bigint_headers bigint_library EXPORT BigIntConfig)
install(EXPORT BigIntConfig NAMESPACE BigInt:: DESTINATION share/BigInt/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/BigIntConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/BigIntConfigVersion.cmake" DESTINATION share/BigInt/cmake)

###################################################################################################
##
##      Тесты
##
###################################################################################################

if(NOT BIGINT_TESTING)
    message(STATUS "Тестирование проекта BigInt выключено")
else()
    add_subdirectory(test)
endif()

###################################################################################################
##
##      Документация
##
###################################################################################################
