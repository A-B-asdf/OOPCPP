######################## GTEST ########################
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

######################## CHECK ########################
add_custom_target(check ALL COMMAND gol-unit-tests)

####################### SOURCES #######################
add_executable(gol-unit-tests test_main.cpp)
target_sources(gol-unit-tests PRIVATE test.cpp)
target_link_libraries(gol-unit-tests
    PRIVATE
        Sources
        gtest gtest_main
)
