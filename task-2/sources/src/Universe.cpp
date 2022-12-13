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

UniverseParser::UniverseParser(CmdArgs &args) {
    if (args.GetInputFile() == "") {
        this->SetDefaultInputFile();
    }
    else {
        this->_input_file = (std::string) DEFAULT_INPUT_DIR + args.GetInputFile();
    }
}

void UniverseParser::SetDefaultInputFile() {
    std::vector<std::string> names;
    names.emplace_back("Glider");
    names.emplace_back("Blinkership");
    names.emplace_back("Blocker");
    names.emplace_back("Enretard");
    names.emplace_back("Gggwfishhook");
    names.emplace_back("Gosperglidergun");
    names.emplace_back("Piorbital");
    std::srand(time(NULL));
    this->_input_file = (std::string) DEFAULT_INPUT_DIR + names.at(std::rand() % names.size()) + ".txt";
    std::cout << "Input file was set bu default:\n\t" << this->_input_file << '\n';
}

void UniverseParser::AddNumber2Born(int a, Universe &universe) {
    universe._cells_number_to_born.insert(a);
}

void UniverseParser::AddNumber2Stay(int a, Universe &universe) {
    universe._cells_number_to_stay.insert(a);
}

void UniverseParser::Parse(Universe &universe) {
    std::ifstream in;
    std::string line;
    in.open(this->_input_file, std::ios::in);
    if (!in.is_open()) {
        std::cout << "ex: no input file\n";
        throw;
    }
    if (in.eof()) {
        std::cout << "ex: input file is empty\n";
        throw;
    }
    HandleFormatLine(line, in);
    HandleNameLine(line, in, universe);
    HandleRulesLine(line, in, universe);
    ParseCells(line, in, universe);
    in.close();    
}

void UniverseParser::HandleFormatLine(std::string &line, std::ifstream &in) {
    std::getline(in, line);
    if (line != "#Life 1.06") {
        std::cout << "ex: Incorrect file format string \n";
        throw;
    }
}

void UniverseParser::HandleNameLine(std::string &line, std::ifstream &in, Universe &universe) {
    std::getline(in, line);
    std::regex rgx("#N (.+)");
    std::smatch match;
    if (!std::regex_search(line, match, rgx)) {
        std::cout << "ex: Bad file format : name\n";
        throw;
    }
    universe.SetName(match[1]);
}

void UniverseParser::HandleRulesLine(std::string &line, std::ifstream &in, Universe &universe) {
    std::getline(in, line);  // third line - Rules
    std::regex b_rgx("#R B(\\d+)/S\\d+");
    std::regex s_rgx("#R B\\d+/S(\\d+)");
    std::smatch b_match;
    std::smatch s_match;
    if (!std::regex_search(line, b_match, b_rgx) 
        || !std::regex_search(line, s_match, s_rgx)) {
        std::cout << "ex: bad file format : rules\n";
        throw;
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
    };
}

void UniverseParser::ParseCells(std::string &line, std::ifstream &in, Universe &universe) {
    int line_counter = 4;
    while (std::getline(in, line)) {
        std::pair<int, int> coords;
        try {
            coords.first = std::stoi(line);
            coords.second = std::stoi(line.substr(line.find(" ")));
        }
        catch(...) {
            std::cout << "ex: something wrong at line " << line_counter << "\n";
            throw;
        }
        universe.SetCell(
            coords.first + universe.RowCount() / 2, 
            coords.second + universe.ColCount() / 2, 
            true
        );
        ++line_counter;
    }
}
