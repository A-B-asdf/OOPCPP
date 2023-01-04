#pragma once

#include <string>
#include <vector>
#include <set>
#include <cmath> // for abs
#include "CmdArgs.hpp"
#include "Cell.hpp"
#include "Universe.hpp"
#include "Controllers.hpp"

#ifndef DEFAULT_INPUT_DIR
#define DEFAULT_INPUT_DIR ""
#endif


#ifndef DEFAULT_OUTPUT_DIR
#define DEFAULT_OUTPUT_DIR ""
#endif

class UniverseParser {
private:
    std::string _input_file;
    void SetDefaultInputFile();

    void HandleFormatLine(std::ifstream&);
    std::string HandleNameLine(std::ifstream&);
    struct Rules HandleRulesLine(std::ifstream&);
    std::vector<std::pair<int, int>> ParseCells(std::ifstream&);
public:
    UniverseParser() = default;
    UniverseParser(std::string &input_file);

    void ParseFromFile(Universe&, GameController &controller);
};
