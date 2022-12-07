#pragma once
#include <string>

class BigInt {
    bool is_neg = false;
    std::string val = "";
private:
    void RemoveZero();
    void ReverseVal();
    void ComplementWithZeros(std::string&, std::string&);
    void BinaryBitOperation(const BigInt&, char operation);
public:
    std::string ToBinaryString() const;  // todo: private
    void BigIntFromSignedBinary(std::string&);
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
