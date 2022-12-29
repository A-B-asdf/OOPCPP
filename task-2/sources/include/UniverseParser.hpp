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

    void HandleFormatLine(std::string&, std::ifstream&);
    void HandleNameLine(std::string&, std::ifstream&, Universe&);
    void HandleRulesLine(std::string&, std::ifstream&, GameController&);
    void ParseCells(std::string&, std::ifstream&, Universe&);
public:
    UniverseParser() = default;
    UniverseParser(CmdArgs&);

    void Parse(Universe&, GameController &controller);
};
