set(BIGINT_DOCTEST_VERSION 2.3.4)
set(BIGINT_DOCTEST_REPOSITORY https://github.com/doctest/doctest.git)

find_package(doctest ${BIGINT_DOCTEST_VERSION})

if (doctest_FOUND)
    message(STATUS "Найден doctest ${doctest_VERSION}: ${doctest_DIR}")
else()
    message(STATUS
        "doctest ${BIGINT_DOCTEST_VERSION} будет взят с гитхаба: ${BIGINT_DOCTEST_REPOSITORY}")

    include(FetchContent)
    FetchContent_Declare(doctest
        GIT_REPOSITORY
            ${BIGINT_DOCTEST_REPOSITORY}
        GIT_TAG
            ${BIGINT_DOCTEST_VERSION}
    )
    FetchContent_MakeAvailable(doctest)
endif()
