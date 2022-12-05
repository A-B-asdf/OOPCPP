#include "BigInt.cpp"
#include <gtest/gtest.h>
#include <iostream>

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

TEST(operator_g, diffneg) {
    BigInt A = BigInt(1), B = BigInt(-1);
    ASSERT_EQ(A > B, true);
    ASSERT_EQ(B > A, false);
}

TEST(operator_le, l) {
    BigInt A = BigInt(-1), B = BigInt(1);
    ASSERT_EQ(A <= B, true);
    ASSERT_EQ(B <= A, false);
}

TEST(operator_le, e) {
    BigInt A = BigInt(1), B = BigInt(1);
    ASSERT_EQ(A <= B, true);
    ASSERT_EQ(B <= A, true);
}

TEST(operator_ge, g) {
    BigInt B = BigInt(-1), A = BigInt(1);
    ASSERT_EQ(A >= B, true);
    ASSERT_EQ(B >= A, false);
}

TEST(operator_ge, e) {
    BigInt B = BigInt(1), A = BigInt(1);
    ASSERT_EQ(A >= B, true);
    ASSERT_EQ(B >= A, true);
}

TEST(operator_int, pos) {
    BigInt A = BigInt(1234);
    ASSERT_EQ((int) A, 1234);
}

TEST(operator_int, neg) {
    BigInt A = BigInt(-1234);
    ASSERT_EQ((int) A, -1234);
}

TEST(operator_plus_eq, is_neg_eq) {
    // BigInt& BigInt::operator+=(const BigInt& a) case 1
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A += B;
    B += A;
    ASSERT_EQ(A, BigInt(a + b));
    ASSERT_EQ(B, BigInt(a + b + b));
}

TEST(operator_plus_eq, is_neg_ne) {
    int a = 1234, b = -123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A += B;
    B += A;
    ASSERT_EQ(A, BigInt(a + b));
    ASSERT_EQ(B, BigInt(a + b + b));
}

TEST(unary_plus, zxc) {
    BigInt A = BigInt(1234), B;
    B = +A;
    ASSERT_EQ(B, A);
}

TEST(unary_minus, zxc) {
    int a = 1234;
    BigInt A = BigInt(a), B;
    B = -A;
    ASSERT_EQ(B, BigInt(-a));
    ASSERT_EQ(A, BigInt(a));
}

TEST(operator_minus_eq, f_lower) {
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A -= B;
    ASSERT_EQ(A, BigInt(a - b));
    ASSERT_EQ(B, BigInt(B));
}

TEST(operator_minus_eq, f_upper) {
    int a = 3, b = 100;
    BigInt A = BigInt(a), B = BigInt(b);
    B -= A;
    ASSERT_EQ(B, BigInt(b - a));
    ASSERT_EQ(A, BigInt(A));
}

TEST(operator_minus_eq, is_neg_dif) {
    int a = 3, b = 100;
    BigInt A = BigInt(a), B = BigInt(b);
    A -= B;
    ASSERT_EQ(A, BigInt(a-b));
}

TEST(operator_plusplus, zxc) {
    int a = 1234;
    BigInt A = BigInt(a), B;
    B = A++;
    ASSERT_EQ(A, BigInt(a + 1));
    ASSERT_EQ(B, BigInt(a));
}

TEST(operator_minusminus, zxc) {
    int a = 1234;
    BigInt A = BigInt(a), B;
    B = A--;
    ASSERT_EQ(A, BigInt(a - 1));
    ASSERT_EQ(B, BigInt(a));
}

TEST(operator_plusplus_int, zxc) {
    int a = 1234;
    BigInt A = BigInt(a), B;
    B = ++A;
    ASSERT_EQ(A, BigInt(a + 1));
    ASSERT_EQ(B, BigInt(a + 1));
}

TEST(operator_minusminus_int, zxc) {
    int a = 1234;
    BigInt A = BigInt(a), B;
    B = --A;
    ASSERT_EQ(A, BigInt(a - 1));
    ASSERT_EQ(B, BigInt(a - 1));
}

TEST(operator_mul_ass, pospos) {
    int a = 1234, b = 5432;

    BigInt A = BigInt(a), B = BigInt(b);
    A *= B;
    B *= B;
    ASSERT_EQ(A, BigInt(a * b));
    ASSERT_EQ(B, BigInt(b * b));
}

TEST(operator_mul_ass, negpos) {
    int a = -1234, b = 5432;

    BigInt A = BigInt(a), B = BigInt(b);
    A *= B;
    B *= B;
    ASSERT_EQ(A, BigInt(a * b));
    ASSERT_EQ(B, BigInt(b * b));
}

TEST(operator_mul_ass, negneg) {
    int a = -1234, b = -5432;

    BigInt A = BigInt(a), B = BigInt(b);
    A *= B;
    B *= B;
    ASSERT_EQ(A, BigInt(a * b));
    ASSERT_EQ(B, BigInt(b * b));
}

TEST(operator_div_ass, zxc) {
    int a = 100, b = 3;
    BigInt A = BigInt(a), B = BigInt(b);
    A /= B;
    ASSERT_EQ(A, BigInt(a / b));
    ASSERT_EQ(B, BigInt(b));
}

TEST(operator_div_ass, div_by_0) {
    int a = 100, b = 0;
    BigInt A = BigInt(a), B = BigInt(b);
    EXPECT_ANY_THROW(A /= B);
}

TEST(operator_mod_ass, zxc) {
    int a = 100, b = 3;
    BigInt A = BigInt(a), B = BigInt(b);
    A %= B;
    ASSERT_EQ(A, BigInt(a % b));
    ASSERT_EQ(B, BigInt(b));
}

TEST(operator_mod_ass, div_by_0) {
    int a = 100, b = 0;
    BigInt A = BigInt(a), B = BigInt(b);
    EXPECT_ANY_THROW(A %= B);
}

TEST(operator_plus, is_neg_eq) {
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A += B;
    B += A;
    ASSERT_EQ(A, BigInt(a + b));
    ASSERT_EQ(B, BigInt(a + b + b));
}

TEST(operator_mul, zxc) {
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A *= B;
    ASSERT_EQ(A, BigInt(a * b));
}

TEST(operator_div, zxc) {
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A /= B;
    ASSERT_EQ(A, BigInt(a / b));
}

TEST(operator_mod, zxc) {
    int a = 1234, b = 123456;
    BigInt A = BigInt(a), B = BigInt(b);
    A %= B;
    ASSERT_EQ(A, BigInt(a % b));
}


