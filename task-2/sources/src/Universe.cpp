#include "Universe.hpp"
#include <fstream>
#include <regex>

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

void Universe::Save2File(std::string &filepath) {
    std::ofstream out(filepath);
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
                out << x << " " << y << "\n";
            }
        }
    }
    out.close();
}

std::ostream& operator<<(std::ostream& o, const Universe& universe) {
    o << universe._name       << "\n";
    o << "Rules: B";
    for (int num : universe._cells_number_to_born) {
        o << num;
    }
    o << "/S";
    for (int num : universe._cells_number_to_stay) {
        o << num;
    }
    o << "\n";
    for (int x = 0; x < universe._size.first; ++x) {
        for (int y = 0; y < universe._size.second; ++y) {
            std::cout << universe._field.at(x).at(y);
        }
        std::cout << "\n";
    }
    return o;
}

UniverseParser::UniverseParser(CmdArgs &args) {
    this->SetInputFile(args);
}

void UniverseParser::SetInputFile(CmdArgs &args) {
    if (args.GetInputFile() == "") {
        this->SetDefaultInputFile();
    }
    else {
        this->_input_file = args.GetInputFile();
    }
}

void UniverseParser::SetDefaultInputFile() {
    ; // todo
}

void UniverseParser::AddNumber2Born(int a, Universe &universe) {
    universe._cells_number_to_born.insert(a);
}

void UniverseParser::AddNumber2Stay(int a, Universe &universe) {
    universe._cells_number_to_stay.insert(a);
}

void UniverseParser::AddCell(std::pair<int, int>& coords, Universe &universe) {
    if (coords.first >= universe._size.first - 1) {
        universe._field.resize(coords.first + 2);
        for (int i = universe._size.first; i < coords.first + 2; ++i) {
            universe._field[i].resize(universe._size.second, Cell());
        }
        universe._size.first = coords.first + 2;
    }
    if (coords.second >= universe._size.second - 1) {
        for (int i = 0; i < universe._size.first ; ++i) {
            universe._field[i].resize(coords.second + 2, Cell());
        }
        universe._size.second = coords.second + 2;
    }
    
    universe._field.at(coords.first).at(coords.second).SetAlive(true);
    // todo: работа с отрицательными координатами - смещение
}

void UniverseParser::Parse(Universe &universe) {  // todo: распихать по методам
    std::string line;
    std::ifstream in;
    in.open(this->_input_file, std::ios::in);
    if (!in.is_open()) {
        throw(std::exception()); // todo
    }
    if (in.eof()) {
        throw(std::exception()); // todo
    }
    std::getline(in, line);  // first line - file firmat
    // todo: check 1 line
    std::getline(in, line);  // second line - name
    // todo: check 2 line
    universe.SetName(line.substr(3, line.size() - 3));
    std::getline(in, line);  // third line - Rules
    std::regex b_rgx("#R B(\\d+)/S\\d+");
    std::regex s_rgx("#R B\\d+/S(\\d+)");
    std::smatch b_match;
    std::smatch s_match;
    if (!std::regex_search(line, b_match, b_rgx) 
        || !std::regex_search(line, s_match, s_rgx)) {
        std::cout << "BAD INPUT\n";  // todo
    }
    else {
        for (int i = 0; i < b_match[1].length(); ++i) {
            int new_num = b_match[1].str()[i] - '0';
            this->AddNumber2Born(new_num, universe);
        }
        for (int i = 0; i < s_match[1].length(); ++i) {
            int new_num = s_match[1].str()[i] - '0';
            this->AddNumber2Stay(new_num, universe);
        }
    }
    while (std::getline(in, line)) {
        // todo: check line
        std::pair<int, int> coords;
        coords.first = std::stoi(line);
        coords.second = std::stoi(line.substr(line.find(" ")));
        AddCell(coords, universe);
    }
    in.close();
    
}
