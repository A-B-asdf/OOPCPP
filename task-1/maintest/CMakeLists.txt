add_executable(maintest main.cpp)
target_link_libraries(maintest
    PRIVATE
        BigInt::library
)
