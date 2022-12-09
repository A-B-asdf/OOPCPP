#include "Cell.hpp"

const bool& Cell::IsAlive() const {
    return this->_is_alive;
}

void Cell::SetAlive(bool) {}

Cell& Cell::operator=(const Cell&) {}
