#include <bigint/header.hpp>
#include <stdexcept>
#include <iostream>

void BigInt::RemoveZeroes() {
    size_t index = 0;

    while (this->val[index] == '0' && index < this->val.size()) {
        ++index;
    }
    if (index == this->val.size()) {
        this->val = "0";
    }
    else {
        this->val = this->val.substr(index, this->val.size() - index);
    }
    if (this->val == "0") {
        this->is_neg = false;
    }
}

std::string BigInt::ReverseString(std::string& str) const {
    str = std::string(str.crbegin(), str.crend());
    return str;
}

bool AbsLower(const BigInt& a, const BigInt& b) {
    return (a.val.size() < b.val.size() || (a.val.size() == b.val.size() && a.val < b.val));
}

void BigInt::InvertString(std::string& binary) const {
    for (size_t i = 0; i < binary.size(); ++i) {
        binary[i] = (binary[i] == '0') ? '1' : '0';
    }
}

void BigInt::Complement2EqualLen(std::string& str1, std::string& str2) {
    size_t len1 = str1.size() - 1;
    size_t len2 = str2.size() - 1;
    std::string str000 = "";
    
    if (len1 > len2) {
        size_t diff = len1 - len2;
        len2 = len1;
        for (size_t i = 0; i < diff; ++i) {
            str000 += str2[0];
        }
        str2 = str000 + str2;
    }
    else {
        size_t diff = len2 - len1;
        len1 = len2;
        for (size_t i = 0; i < diff; ++i) {
            str000 += str1[0];
        }
        str1 = str000 + str1;
    }
}

std::string BigInt::GetBinaryString() const {
    std::string result = "";
    BigInt this_copy = *this;
    this_copy.is_neg = false;

    if (this->is_neg) {
        --this_copy;  // magic of two’s complement
    }
    do {
        result += '0' + this_copy % BigInt(2);
        this_copy /= BigInt(2);
    } while (this_copy > BigInt());
    result = "0" + ReverseString(result);
    if (this->is_neg) {
        InvertString(result);
    }
    return result;
}

void BigInt::BigIntFromSignedBinary(std::string& binary) {
    *this = BigInt();
    size_t index = binary.size() - 1;
    BigInt deg2 = BigInt(1);

    while (index > 0) {
        char current = binary[index];
        if ((current == '1' && binary[0] == '0') 
                || (current == '0' && binary[0] == '1')) {
            *this += deg2;
        }
        deg2 *= BigInt(2);
        --index;
    }
    if (binary[0] == '1') {
        *this += 1;
        this->is_neg = true;
    }
}

void BigInt::BinaryBitOperation(const BigInt& a, char operation) {
    std::string str1 = this->GetBinaryString();
    std::string str2 = a.GetBinaryString();

    Complement2EqualLen(str1, str2);
    for (size_t i = 0; i < str1.size(); ++i) {
        switch (operation) {
        case '^':
            str1[i] = (str1[i] != str2[i]) ? '1' : '0';
            break;
        case '&':
            str1[i] = ((str1[i] - '0') && (str2[i] - '0')) ? '1' : '0';
            break;
        case '|':
            str1[i] = ((str1[i] - '0') || (str2[i] - '0')) ? '1' : '0';
            break;
        }
    }
    BigIntFromSignedBinary(str1);
}

BigInt::BigInt() {
    this->is_neg = false;
    this->val = "0";
}

BigInt::BigInt(int a) {
    if (a < 0) { 
        is_neg = true;  
        a = -a;  
    } 
    do { 
        int c = a % 10; 
        this->val += (char) c + '0'; 
        a /= 10; 
    } while(a > 0); 
    ReverseString(this->val); 
}

BigInt::BigInt(std::string str) { 
    size_t size = str.size(); 
    char first = str[0];
    size_t index = 0;
    int begining = 0;

    if (first == '-') { 
        is_neg = true;
        index = 1;
        begining = 1;
    }
    if (index == size) {
        throw std::invalid_argument("NaN"); 
    }
    for (; index < size; ++index) { 
        if (str[index] < '0' || str[index] > '9') {
            throw std::invalid_argument("NaN"); 
        }
    }
    this->val = str.substr(begining, size - begining);
    this->RemoveZeroes();
}

BigInt::BigInt(const BigInt& i) { 
    this->is_neg = i.is_neg;
    this->val = "";
    this->val += i.val;
}

BigInt::~BigInt() {
    ;
}

BigInt& BigInt::operator=(const BigInt& a) {  
    if (this != &a) {
        this->is_neg = a.is_neg;
        this->val = "";
        this->val += a.val;
    }
    return *this;
}

BigInt BigInt::operator~() const {
    std::string str = GetBinaryString();
    InvertString(str);
    BigInt result = BigInt();
    result.BigIntFromSignedBinary(str);
    return result;
}

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
    if (a == BigInt(0)) {
        return *this;
    }
    if (this->is_neg != a.is_neg) {
        *this -= -a;
        return *this;
    }
    else {
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
}

BigInt& BigInt::operator*=(const BigInt& a) {
    BigInt this_copy = *this;
    this_copy.is_neg = (this->is_neg != a.is_neg);
    BigInt a_copy = a;
    a_copy.is_neg = false;
    *this = 0;
    for (BigInt i = BigInt(); i < a_copy; ++i) {
        *this += this_copy;
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& a) {
    if (this->is_neg != a.is_neg) {
        *this += -a;
        return *this;
    }
    else if (AbsLower(*this, a)) {
        BigInt result = a;
        result -= *this;
        *this = -result;
        return *this;
    }
    else {
        BigInt result = *this;
        result.val = "";
        result.is_neg = this->is_neg;
        size_t index1 = this->val.size() - 1;
        size_t index2 = a.val.size() - 1;
        int borrow = 0;

        while (index1 + 1 || borrow) {
            int tmp = -borrow; borrow = 0;
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
        result.RemoveZeroes();
        *this = result;
        return *this;        
    }
}

BigInt& BigInt::operator/=(const BigInt& divider) {
    if (divider == BigInt(0)) {
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");
    }
    BigInt result = BigInt();
    bool res_is_neg = (this->is_neg != divider.is_neg);
    this->is_neg = 0;
    BigInt divider_copy = divider;
    divider_copy.is_neg = false;
    while (*this >= divider_copy) {
        *this -= divider_copy;
        result += BigInt(1);
    }
    if (result.val != "0") {
        result.is_neg = res_is_neg;
    }
    *this = result;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& divider) {
    if (divider == BigInt()) {
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");
    }
    bool this_is_neg = this->is_neg;
    this->is_neg = 0;
    BigInt divider_copy = divider;
    divider_copy.is_neg = false;
    while (*this >= divider_copy) {
        *this -= divider_copy;
    }
    if (this->val != "0") {
        this->is_neg = this_is_neg;
    }
    return *this;
}

BigInt& BigInt::operator^=(const BigInt& a) {
    BinaryBitOperation(a, '^');
    return *this;
}

BigInt& BigInt::operator&=(const BigInt& a) {
    BinaryBitOperation(a, '&');
    return *this;
}

BigInt& BigInt::operator|=(const BigInt& a) {
    BinaryBitOperation(a, '|');
    return *this;
}

BigInt BigInt::operator+() const {
    BigInt result = *this;
    return result;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (this->val != "0") {
        result.is_neg = !this->is_neg;
    }
    return result;
}

bool BigInt::operator==(const BigInt& i) const {
    return 
        (this->is_neg == i.is_neg && this->val == i.val) 
        ? 
        true 
        : 
        false; 
}

bool BigInt::operator!=(const BigInt& i) const {
    return (*this == i) ? false : true;
}

bool BigInt::operator<(const BigInt& i) const {
    if (this->is_neg != i.is_neg) { 
        return (this->is_neg) ? true : false;
    }
    if (this->val.size() != i.val.size()) {
        return (this->is_neg) ? 
            (this->val.size() > i.val.size()) 
            : (this->val.size() < i.val.size());
    }
    for (size_t index = 0; index < this->val.size(); ++index) {
        if (this->val[index] != i.val[index]) {
            return (this->is_neg) ? 
                this->val[index] > i.val[index] 
                : this->val[index] < i.val[index];
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& i) const {
    return i < *this;
}

bool BigInt::operator<=(const BigInt& i) const {
    return *this == i || *this < i;
}

bool BigInt::operator>=(const BigInt& i) const {
    return !(*this < i);
}

BigInt::operator int() const {
    return (this->is_neg) ? -std::stoi(this->val) : std::stoi(this->val);
}

BigInt::operator std::string() const {
    std::string result;

    if (this->is_neg) {
        result += '-';
    }
    result += this->val;
    return result;
}

size_t BigInt::size() const {
    size_t size = 0;
    size += this->val.size() + 1;
    size += sizeof(this->is_neg);
    return size;
}

BigInt BigInt::operator+(const BigInt& a) const {
    BigInt result = *this;
    result += a;
    return result;
}

BigInt BigInt::operator-(const BigInt& a) const {
    BigInt result = *this;
    result -= a;
    return result;
}

BigInt BigInt::operator*(const BigInt& a) const {
    BigInt result = *this;
    result *= a;
    return result;
}

BigInt BigInt::operator/(const BigInt& a) const {
    BigInt result = *this;
    result /= a;
    return result;
}

BigInt BigInt::operator^(const BigInt& a) const {
    BigInt result = *this;
    result ^= a;
    return result;
}

BigInt BigInt::operator%(const BigInt& a) const {
    BigInt result = *this;
    result %= a;
    return result;
}

BigInt BigInt::operator&(const BigInt& a) const {
    BigInt result = *this;
    result &= a;
    return result;
}

BigInt BigInt::operator|(const BigInt& a) const {
    BigInt result = *this;
    result |= a;
    return result;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
    if (i.is_neg) {
        o << '-';
    }
    o << i.val;
    return o;
}
