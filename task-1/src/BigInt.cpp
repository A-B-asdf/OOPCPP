#include <stdexcept>
#include <iostream>
#include "BigInt.h"

void BigInt::RemoveZero() { //*
    size_t index = 0;

    while (this->val[index] == '0') {
        ++index; //
    }
    if (index == this->val.size()) {
        this->val = "0"; //
    }
    else {
        this->val = this->val.substr(index, this->val.size() - index); //
    }
}

void BigInt::ReverseVal() { // *
    size_t size = this->val.size()-1;
    for (size_t i = 0; i <= size / 2; ++i) {
        char c = this->val[i];
        this->val[i] = this->val[size - i];
        this->val[size - i] = c;
    }
}

BigInt::BigInt() { //
    is_neg = false;
    this->val = "0";
}

BigInt::BigInt(int a) { //

    if (a < 0) { //
        is_neg = true;  //
        a = -a;  //
    } //
    do { //
        int c = a % 10; //
        this->val += (char) (c + '0'); //
        a /= 10; //
    } while(a > 0); //
    this->ReverseVal(); //
}

BigInt::BigInt(std::string str) { //
    size_t size = str.size(); 
    char first = str[0];
    size_t index = 0;
    int begining = 0;

    if (size == 0) {
        throw std::invalid_argument("NaN"); //
    }

    if (first == '-') { //
        is_neg = true;
        index = 1;
        begining = 1;
    }
    for (; index < size; ++index) { //
        if (str[index] < '0' || str[index] > '9') {
            throw std::invalid_argument("NaN"); //
        }
    }
    this->val = str.substr(begining, size-begining);
    this->RemoveZero(); //
    if (this->val == "0") { //
        is_neg = false;
    }
}

BigInt::BigInt(const BigInt& i) { //
    this->is_neg = i.is_neg;
    this->val = i.val;
}

BigInt::~BigInt() {
    
}

BigInt& BigInt::operator=(const BigInt& a) {  //
    if (this == &a) {
        return (*this);
    }
    this->is_neg = a.is_neg;
    this->val = a.val;
    return *this;
}

//BigInt operator~() const;  // const  конце - внутри метода не можем менять члены класса

BigInt& BigInt::operator++() {
    *this += 1;
    return *this;
}

const BigInt BigInt::operator++(int) {
    BigInt a = *this;
    *this += 1;
    return a;
}

BigInt& BigInt::operator--() {
    *this -= 1;
    return *this;
}

const BigInt BigInt::operator--(int) {
    BigInt a = *this;
    *this -= 1;
    return a;
}

BigInt& BigInt::operator+=(const BigInt& a) {
    if (this->is_neg == a.is_neg) {
        BigInt result = BigInt();
        result.val = "";
        result.is_neg = this->is_neg;
        size_t index1 = this->val.size() - 1;
        size_t index2 = a.val.size() - 1;
        int carry = 0;

        while (index1 + 1 || index2 + 1 || carry) {
            int tmp = 0;
            if (index1 + 1) {
                tmp += (int) this->val[index1] - '0';
                --index1;
            }
            if (index2 + 1) {
                tmp += (int) a.val[index2] - '0';
                --index2;
            }
            tmp += carry;
            result.val.insert(0, 1, (char) tmp % 10 + '0');
            carry = tmp / 10;

        }
        *this = result;
        return *this;        
    }
    else {
        *this -= -a;
        return *this;
    }
}

BigInt& BigInt::operator*=(const BigInt& a) {
    BigInt this_cp = *this;
    this_cp.is_neg = (this->is_neg != a.is_neg);
    BigInt a_cp = a;
    a_cp.is_neg = false;
    *this = 0;
    for (BigInt i = BigInt(); i < a_cp; ++i) {
        *this += this_cp;
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& a) {
    if (this->is_neg != a.is_neg) {
        *this += -a;
        return *this;
    }
    else if (this->val >= a.val) {
        BigInt result = *this;
        result.val = "";
        result.is_neg = this->is_neg;
        size_t index1 = this->val.size() - 1;
        size_t index2 = a.val.size() - 1;
        int borrow = 0;

        while (index1 + 1 || borrow) {
            int tmp = -borrow; borrow = 0; // todo
            if (index1 + 1) {
                tmp += (int) this->val[index1] - '0';
                --index1;
            }
            if (index2 + 1) {
                tmp -= (int) a.val[index2] - '0';
                --index2;
            }
            if (tmp < 0) {
                tmp += 10;
                borrow = 1;
            }
            result.val.insert(0, 1, (char) tmp + '0');
        }
        *this = result;
        return *this;        
    }
    else {
        BigInt result = a;
        result -= *this;
        *this = -result;
        return *this;
    }
}

//BigInt& BigInt::operator/=(const BigInt&);
//BigInt& BigInt::operator^=(const BigInt&);
//BigInt& BigInt::operator%=(const BigInt&);
//BigInt& BigInt::operator&=(const BigInt&);
//BigInt& BigInt::operator|=(const BigInt&);

BigInt BigInt::operator+() const {  // unary +
    BigInt result = *this;
    return result;
}

BigInt BigInt::operator-() const {  // unary -
    BigInt result = *this;
    result.is_neg = !this->is_neg;
    return result;
}

bool BigInt::operator==(const BigInt& i) const { //
    return 
        (this->is_neg == i.is_neg && this->val == i.val) 
        ? 
        true 
        : 
        false; 
}

bool BigInt::operator!=(const BigInt& i) const { //
    return (*this == i) ? false : true;
}

bool BigInt::operator<(const BigInt& i) const {
    if (this->is_neg != i.is_neg) {  //
        return (this->is_neg) ? true : false;
    }
    if (this->val.size() != i.val.size()) {  //
        return (this->is_neg) ? 
            (this->val.size() > i.val.size()) : 
            (this->val.size() < i.val.size());
    }
    for (size_t index = 0; index < this->val.size(); ++index) {
        if (this->val[index] != i.val[index]) {
            return (this->is_neg) ? 
                this->val[index] > i.val[index] :
                this->val[index] < i.val[index];
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& i) const { //
    return i < *this;
}

bool BigInt::operator<=(const BigInt& i) const { //
    return *this == i || *this < i;
}

bool BigInt::operator>=(const BigInt& i) const { //
    return !(*this < i);
}

BigInt::operator int() const {
    return (! this->is_neg) ? std::stoi(this->val) : -std::stoi(this->val);
}

BigInt::operator std::string() const {
    std::string result;
    if (this->is_neg) {
        result += '-';
    }
    result += this->val;
    return result;
}

//size_t size() const;  // size in bytes

//BigInt operator+(const BigInt&, const BigInt&);
//BigInt operator-(const BigInt&, const BigInt&);
//BigInt operator*(const BigInt&, const BigInt&);
//BigInt operator/(const BigInt&, const BigInt&);
//BigInt operator^(const BigInt&, const BigInt&);
//BigInt operator%(const BigInt&, const BigInt&);
//BigInt operator&(const BigInt&, const BigInt&);
//BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i) {

    if (i.is_neg) {
        o << '-';
    }
    o << i.val;
    return o;
}
