#include "UniverseParser.hpp"
#include <fstream>
#include <regex>

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
