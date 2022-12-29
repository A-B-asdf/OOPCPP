#include "Universe.hpp"
#include <fstream>
#include <regex>

int mod(int n, int d) {
    int result = n % d;
    if (result < 0)
        result += d;
    return result;
}

Universe::Universe() {
    this->_field.resize(this->_size.first);
    for (int i = 0; i < this->_size.first; ++i) {
        this->_field[i].resize(this->_size.second);
    }
}

bool Universe::IsCellAlive(int x, int y) {

    return this->_field
            .at(mod(x, this->_size.first))
            .at(mod(y, this->_size.second))
            .IsAlive();
}

void Universe::SetCell(int x, int y, bool is_alive) {
    if (x < 0 || x >= this->_size.first || y < 0 || y >= this->_size.second) {
        std::cout << "Sorry, don wanna resize the field now. ex: out of range\n";
        throw;
    }
    return this->_field.at(x).at(y).SetAlive(is_alive);
}

void Universe::SetSize(std::pair<int, int> &size) {
    this->_size = size;
}

void Universe::SetName(const std::string &name) {
    this->_name = name;
}

std::string Universe::GetName() {
    return this->_name;
}

std::pair<int, int> Universe::GetSize() {
    return this->_size;
}
