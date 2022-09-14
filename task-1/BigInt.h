//
// Created by Alex on 14.09.2022.
//

#ifndef INC_21202_BIRYUKOV_OOP_CPP_BIGINT_H
#define INC_21202_BIRYUKOV_OOP_CPP_BIGINT_H  // todo: че это блин


class BigInt {
public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!
    /*
     * int a = 3, b, c;
     * b = c = a;
     * //т.е. оператор должен вернуть this
     * // note: в статическом методе нет указателя на this
     */
    BigInt operator~() const;  // const  конце - внутри метода не можем менять члены класса

    BigInt& operator++();
    const BigInt operator++(int) const;
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);

/*
 * Нужно написать тесты, которые проверяют, что бигинт работает верно
 * Google Test Framework
 * TestSum(BigInt, sum) {
 *     BigInt n1("123");
 *     BigInt n2("321");
 *     ASSwhat?_EQ(444, n1+n2);
 * }
 */

#endif //INC_21202_BIRYUKOV_OOP_CPP_BIGINT_H
