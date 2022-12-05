#include <string>

class BigInt {
    bool is_neg = false;
    std::string val = "";
private:
    void RemoveZero();
    void ReverseVal();
public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt&);
    
    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+(const BigInt&);
    BigInt operator-(const BigInt&);
    BigInt operator*(const BigInt&);
    BigInt operator/(const BigInt&);
    BigInt operator^(const BigInt&);
    BigInt operator%(const BigInt&);
    BigInt operator&(const BigInt&);
    BigInt operator|(const BigInt&);

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

    friend std::ostream& operator<<(std::ostream& o, const BigInt& i);
};


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
