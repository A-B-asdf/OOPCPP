# Build googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(bigint-unit-tests test_main.cpp)
target_sources(bigint-unit-tests PRIVATE bigint/test.cpp)
target_link_libraries(bigint-unit-tests
    PRIVATE
        BigInt::library
        gtest gtest_main
)

find_program(GCOVR_EXECUTABLE lcov)
if(BIGINT_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(bigint-unit-tests PRIVATE --coverage)
    target_link_options(bigint-unit-tests PRIVATE -fprofile-arcs)

    target_compile_options(bigint_library PRIVATE --coverage)
    target_link_options(bigint_library PRIVATE -fprofile-arcs)

    add_custom_target(coverage ALL
        COMMAND echo "=================== GCOV ===================="
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${PROJECT_SOURCE_DIR}/
                --filter=${PROJECT_SOURCE_DIR}/include
                --filter=${PROJECT_SOURCE_DIR}/src
                --object-directory=${PROJECT_BINARY_DIR}
        DEPENDS
            check
    )
elseif(BIGINT_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(BIGINT_COVERAGE OFF)
    message(WARNING "Для замеров покрытия кода тестами требуется программа gcovr")
endif()

add_custom_target(check ALL COMMAND bigint-unit-tests)
