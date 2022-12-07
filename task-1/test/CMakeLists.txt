# Build googletest
add_subdirectory(
    "${PROJECT_SOURCE_DIR}/googletest"
    "googletest"
)

add_executable(bigint-unit-tests test_main.cpp)
target_sources(bigint-unit-tests PRIVATE bigint/test.cpp)
target_link_libraries(bigint-unit-tests
    PRIVATE
        BigInt::library
        gtest gtest_main
)

find_program(GCOVR_EXECUTABLE gcovr)
if(BIGINT_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(bigint-unit-tests PRIVATE --coverage)
    target_link_options(bigint-unit-tests PRIVATE -fprofile-arcs)

    target_compile_options(bigint_library PRIVATE --coverage)
    target_link_options(bigint_library PRIVATE -fprofile-arcs)

    add_custom_target(coverage
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
