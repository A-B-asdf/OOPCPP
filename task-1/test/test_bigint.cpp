#include "BigInt.cpp"
#include <gtest/gtest.h>
namespace {
    TEST(operator_equal, Self_positive) {
        BigInt A = BigInt(1234);
        ASSERT_EQ(A, A);
    }

    TEST(operator_equal, Self_negative) {
        BigInt A = BigInt(-1234);
        ASSERT_EQ(A, A);
    }

    TEST(operator_equal, equal) {
        BigInt A = BigInt(1234);
        BigInt B = BigInt(1234);
        ASSERT_EQ(A, B);
    }

    TEST(operator_equal, val) {
        BigInt A = BigInt(1234);
        BigInt B = BigInt(4321);
        ASSERT_NE(A, B);
    }

    TEST(operator_equal, sign) {
        BigInt A = BigInt(1234);
        BigInt B = BigInt(-1234);
        ASSERT_NE(A, B);
    }

    TEST(operator_equal, val_and_sign) {
        BigInt A = BigInt(1234);
        BigInt B = BigInt(-4321);
        ASSERT_NE(A, B);
    }
}

namespace Init_from_string {
    TEST(Init_from_string, incorrect_empty) {
        ASSERT_ANY_THROW(BigInt(static_cast<std::string>("")));
    }

    TEST(Init_from_string, incorrect_symbol) {
        ASSERT_ANY_THROW(BigInt(static_cast<std::string>("-12 34")));
    }

    TEST(Init_from_string, uncountable) {
        BigInt A = BigInt("12345");
        BigInt B = BigInt(12345);
        ASSERT_EQ(A, B);
    }

    TEST(Init_from_string, countable) {
        BigInt A = BigInt("123456");
        BigInt B = BigInt(123456);
        ASSERT_EQ(A, B);
    }

    TEST(Init_from_string, negative) {
        BigInt A = BigInt("12345");
        BigInt B = BigInt(12345);
        ASSERT_EQ(A, B);
    }

    TEST(Init_from_string, zero) {
        BigInt A = BigInt("-0");
        BigInt B = BigInt(0);
        ASSERT_EQ(A, B);
    }

    TEST(Init_from_string, remove_zeroes) {
        BigInt A = BigInt("000001234");
        BigInt B = BigInt(1234);
        ASSERT_EQ(A, B);
    }

    TEST(Init_from_string, remove_zeroes_from_zero) {
        BigInt A = BigInt("00000");
        BigInt B = BigInt(0);
        ASSERT_EQ(A, B);
    }
}

namespace Init {
    TEST(Init, pure) {
        BigInt A = BigInt();
        BigInt B = BigInt(0);
        ASSERT_EQ(A, B);
    }

    TEST(Init, another_bigint) {
        BigInt A = BigInt(-123);
        BigInt B = BigInt(A);
        ASSERT_EQ(A, B);
    }
}

TEST(operator_assignment, ABC) {
    BigInt A = BigInt(-1234), B, C;
    B = C = A;
    ASSERT_EQ(A, B);
    ASSERT_EQ(A, C);
}

/*
TEST(operator_plus, ok) {
    BigInt A = BigInt(-123);
    A = A + A;
    ASSERT_EQ(A, BigInt(-123 * 2));
}
*/

TEST(operator_l, diffneg) {
    BigInt A = BigInt(-1), B = BigInt(1);
    ASSERT_EQ(A < B, true);
    ASSERT_EQ(B < A, false);
}

TEST(operator_l, eq_pos) {
    BigInt A = BigInt(1), B = BigInt(1);
    ASSERT_EQ(A < B, false);
}

TEST(operator_l, eq_neg) {
    BigInt A = BigInt(-1), B = BigInt(-1);
    ASSERT_EQ(A < B, false);
}

TEST(operator_l, difsize_pos) {
    BigInt A = BigInt(1234), B = BigInt(12345);
    ASSERT_EQ(A < B, true);
    ASSERT_EQ(B < A, false);
}

TEST(operator_l, difsize_neg) {
    BigInt A = BigInt(-1234), B = BigInt(-12345);
    ASSERT_EQ(A < B, false);
    ASSERT_EQ(B < A, true);
}

TEST(operator_l, eqsize_pos) {
    BigInt A = BigInt(1234), B = BigInt(1240);
    ASSERT_EQ(A < B, true);
    ASSERT_EQ(B < A, false);
}

TEST(operator_l, eqsize_neg) {
    BigInt A = BigInt(-1234), B = BigInt(-1240);
    ASSERT_EQ(A < B, false);
    ASSERT_EQ(B < A, true);
}
