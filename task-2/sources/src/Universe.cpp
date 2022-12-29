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

bool Universe::IsCellAliveNext(int x, int y) {
    int sum = 0;
    if (IsCellAlive(x    , y - 1)) ++sum;
    if (IsCellAlive(x    , y + 1)) ++sum;
    if (IsCellAlive(x - 1, y    )) ++sum;
    if (IsCellAlive(x - 1, y - 1)) ++sum;
    if (IsCellAlive(x - 1, y + 1)) ++sum;
    if (IsCellAlive(x + 1, y    )) ++sum;
    if (IsCellAlive(x + 1, y + 1)) ++sum;
    if (IsCellAlive(x + 1, y - 1)) ++sum;
    if (this->IsCellAlive(x, y)) {
        for (int n : _cells_number_to_stay) {
            if (n == sum) {
                return true;
            }
        }
        return false;
    }
    else {
        for (int n : _cells_number_to_born) {
            if (n == sum) {
                return true;
            }
        }
        return false;
    }
}

std::vector<std::pair<int, int>> Universe::GetNextAliveCells(){
    std::vector<std::pair<int, int>> next_alive_cells;
    for (int x = 0; x < this->RowCount(); ++x) {
        for (int y = 0; y < this->ColCount(); ++y) {
            if (this->IsCellAliveNext(x, y)) {
                next_alive_cells.emplace_back();  // todo: говнокод
                next_alive_cells.at(next_alive_cells.size() - 1).first = x;
                next_alive_cells.at(next_alive_cells.size() - 1).second = y;
            }
        }
    }
    return next_alive_cells;
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

void Universe::SetRules(const std::set<int> &cells_number_to_born, const std::set<int> &cells_number_to_stay) {
    this->_cells_number_to_born = cells_number_to_born;
    this->_cells_number_to_stay = cells_number_to_stay;
}

void Universe::SetName(const std::string &name) {
    this->_name = name;
}

int Universe::RowCount() {
    return this->_size.first;
}

int Universe::ColCount() {
    return this->_size.second;
}

void Universe::SetFieldFromAliveCoords(std::vector<std::pair<int, int>> &alive_cells) {
    for (int x = 0; x < this->RowCount(); ++x) {
        for (int y = 0; y < this->ColCount(); ++y) {
            bool is_alive = false;
            for (auto p : alive_cells) {
                if (p.first == x && p.second == y) { // todo: говнокод
                    is_alive = true;
                }
            }
            this->SetCell(x, y, is_alive);
        }
    }
}

void Universe::Tick() {
    std::vector<std::pair<int, int>> next_alive_cells = GetNextAliveCells();
    SetFieldFromAliveCoords(next_alive_cells);
    ++this->_iteration;
}

void Universe::Save2File(std::string &filename) {
    std::ofstream out;
    out.open(filename, std::ios::out);
    if (!out.is_open()) {
        std::cout << "ex: bad output file\n";
        throw;
    }
    out << "#Life 1.06\n";
    out << "#N " << this->_name << "\n";
    out << "#R B";
    for (int num : this->_cells_number_to_born) {
        out << num;
    }
    out << "/S";
    for (int num : this->_cells_number_to_stay) {
        out << num;
    }
    out << "\n";
    for (int x = 0; x < this->_size.first; ++x) {
        for (int y = 0; y < this->_size.second; ++y) {
            if (this->_field.at(x).at(y).IsAlive()) {
                out << x - this->RowCount() / 2 << " " << y - this->ColCount() / 2  << "\n";
            }
        }
    }
    out.close();
}

std::ostream& operator<<(std::ostream& o, const Universe& universe) {
    o << "Name: " << universe._name << "\n";
    o << "Rules: B";
    for (int num : universe._cells_number_to_born) {
        o << num;
    }
    o << "/S";
    for (int num : universe._cells_number_to_stay) {
        o << num;
    }
    o << "\n";
    std::cout << "Iteration: " << universe._iteration << "\n";
    for (int x = 0; x < universe._size.first; ++x) {
        for (int y = 0; y < universe._size.second; ++y) {
            std::cout << universe._field.at(x).at(y);
        }
        std::cout << "\n";
    }
    return o;
}
