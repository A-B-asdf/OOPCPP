#include <stdexcept>
#include <iostream>
#include "BigInt.h"

void BigInt::removeZero() {
    int index = 0;

    while (this->val[index] == '0') {
        ++index;
    }
    if (index == this->val.size()) {
        this->val = "0";
    }
    else {
        this->val = this->val.substr(index, this->val.size() - index);
    }
}

void BigInt::ReverseVal() {
    size_t size = this->val.size()-1;
    for (int i = 0; i < size / 2; ++i) {
        char c = this->val[i];
        this->val[i] = this->val[size - i];
        this->val[size - i] = c;
    }
}

BigInt::BigInt() {
    is_neg = false;
    this->val = "0";
}

BigInt::BigInt(int a) {

    if (a < 0) {
        is_neg = true;
        a = -a;
    }
    do {
        int c = a % 10;
        this->val += (char) (c + '0');
        a /= 10;
    } while(a > 0);
    this->ReverseVal();
}

BigInt::BigInt(std::string str) {
    size_t size = str.size();
    char first = str[0];
    int index = 0;
    int begining = 0;

    if (first == '-') {
        is_neg = true;
        index = 1;
        begining = 1;
    }
    for (; index < size; ++index) {
        if (str[index] < '0' || str[index] > '9') {
            throw std::invalid_argument("NaN");
        }
    }
    this->val = str.substr(begining, size-begining);
    this->removeZero();
    if (this->val == "0") {
        is_neg = false;
    }
}

BigInt::BigInt(const BigInt& i) {
    this->is_neg = i.is_neg;
    this->val = i.val;
}

BigInt::~BigInt() {
    
}



std::ostream& operator<<(std::ostream& o, const BigInt& i) {

    if (i.is_neg) {
        o << '-';
    }
    o << i.val;
    return o;
}
