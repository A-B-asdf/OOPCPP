#include "UniverseParser.hpp"
#include <fstream>
#include <regex>

UniverseParser::UniverseParser(std::string &input_file) {
    if (input_file == "") {
        this->SetDefaultInputFile();
    }
    else {
        this->_input_file = (std::string) DEFAULT_INPUT_DIR + input_file;
    }  // doesn't check if file is correct, it will be checked in function ParseFromFile
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
    std::cout << "Input file was set bu default: " << this->_input_file << '\n';
}

void UniverseParser::ParseFromFile(Universe &universe, GameController &controller) {
    std::ifstream in;
    in.open(this->_input_file, std::ios::in);
    if (!in.is_open()) {
        std::cout << "ex: no input file\n";
        throw;
    }
    if (in.eof()) {
        std::cout << "ex: input file is empty\n";
        throw;
    }
    HandleFormatLine(in);
    std::string universe_name = HandleNameLine(in);
    universe.SetName(universe_name);
    struct Rules rules = HandleRulesLine(in);
    controller.SetRules(rules);
    std::vector<std::pair<int, int>> alive_cells = ParseCells(in);
    universe.SetFieldFromAliveCoords(alive_cells);
    in.close();
}

void UniverseParser::HandleFormatLine(std::ifstream &in) {
    std::string line;
    std::getline(in, line);
    if (line != "#Life 1.06") {
        std::cout << "ex: Incorrect file format string \n";
        throw;
    }
}

std::string UniverseParser::HandleNameLine(std::ifstream &in) {
    std::string line;
    std::getline(in, line);
    std::regex rgx("#N (.+)");
    std::smatch match;
    if (!std::regex_search(line, match, rgx)) {
        std::cout << "ex: Bad file format : name\n";
        throw;
    }
    return match[1];
}

struct Rules UniverseParser::HandleRulesLine(std::ifstream &in) {
    std::string line;
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
    struct Rules rules;
    for (int i = 0; i < b_match[1].length(); ++i) {
        int new_num = b_match[1].str()[i] - '0';
        rules.born.insert(new_num);
    }
    for (int i = 0; i < s_match[1].length(); ++i) {
        int new_num = s_match[1].str()[i] - '0';
        rules.stay.insert(new_num);
    }
    return rules;
}

std::vector<std::pair<int, int>> UniverseParser::ParseCells(std::ifstream &in) {
    std::string line;
    std::vector<std::pair<int, int>> alive_cells;
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
        alive_cells.emplace_back();
        alive_cells.at(alive_cells.size() - 1).first = coords.first;
        alive_cells.at(alive_cells.size() - 1).second = coords.second;
        ++line_counter;
    }
    return alive_cells;
}
