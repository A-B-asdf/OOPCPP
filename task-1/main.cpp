#include <iostream>
#include "BigInt.cpp"
#include <gtest/gtest.h>

int main() {
    BigInt A = BigInt("-1234");
    std::cout << std::string(A) << '\n';
    return 0;
}
