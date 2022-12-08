#pragma once
#include <string>

class BigInt {
    bool is_neg = false;
    std::string val = "";
private:
    void RemoveZeroes();
    std::string ReverseString(std::string&) const ;
    friend bool AbsLower(const BigInt&, const BigInt&);
    std::string GetBinaryString() const;
    void BigIntFromSignedBinary(std::string&);
    void Complement2EqualLen(std::string&, std::string&);
    void InvertString(std::string&) const;
    void BinaryBitOperation(const BigInt&, char operation);
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

    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator^(const BigInt&) const;
    BigInt operator%(const BigInt&) const;
    BigInt operator&(const BigInt&) const;
    BigInt operator|(const BigInt&) const;

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
