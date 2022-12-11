#include "Cell.hpp"

const bool& Cell::IsAlive() const {
    return this->_is_alive;
}

void Cell::SetAlive(bool is_alive) {
    this->_is_alive = is_alive;
}

Cell& Cell::operator=(const Cell &cell) {
    if (this != &cell) {
        _is_alive = cell.IsAlive();
    }
    return *this;
}

std::ostream& operator<<(std::ostream &o, const Cell &cell) {
    o << ((cell.IsAlive()) ? '*' : '.');
    return o;
}
