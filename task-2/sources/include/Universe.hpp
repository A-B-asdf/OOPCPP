#pragma once

#include <string>
#include <vector>
#include <set>
#include <cmath> // for abs
#include "CmdArgs.hpp"
#include "Cell.hpp"

#ifndef DEFAULT_INPUT_DIR
#define DEFAULT_INPUT_DIR ""
#endif


#ifndef DEFAULT_OUTPUT_DIR
#define DEFAULT_OUTPUT_DIR ""
#endif

class Universe {
private:
    std::pair<int, int> _size = {60, 100};
    std::set<int> _cells_number_to_born;
    std::set<int> _cells_number_to_stay;
    std::string _name = "Default";
    std::vector<std::vector<Cell>> _field;
    int _iteration = 0;
public:
    Universe();
    Universe(std::pair<int, int> &size, 
             std::set<int> &cells_number_to_born, 
             std::set<int> &cells_number_to_stay, 
             std::string &name
             ) :
        _size(size), 
        _cells_number_to_born(cells_number_to_born), 
        _cells_number_to_stay(cells_number_to_stay),
        _name(name) {}
 
    int RowCount();
    int ColCount();
    bool IsCellAlive(int x, int y);
    bool IsCellAliveNext(int x, int y);
    std::vector<std::pair<int, int>> GetNextAliveCells();
    
    void SetRules(const std::set<int>&, const std::set<int>&);
    void SetName(const std::string&);
    void SetSize(std::pair<int, int> &size);
    void SetCell(int x, int y, bool is_alive);
    void SetFieldFromAliveCoords(std::vector<std::pair<int, int>>&);

    void Tick();

    void Save2File(std::string&);

    friend class UniverseParser;
    friend std::ostream& operator<<(std::ostream&, const Universe&);
};

std::ostream& operator<<(std::ostream&, const Universe&);

class UniverseParser {
private:
    std::string _input_file;
    void SetDefaultInputFile();
    void AddNumber2Born(int, Universe&);
    void AddNumber2Stay(int, Universe&);

    void HandleFormatLine(std::string&, std::ifstream&);
    void HandleNameLine(std::string&, std::ifstream&, Universe&);
    void HandleRulesLine(std::string&, std::ifstream&, Universe&);
    void ParseCells(std::string&, std::ifstream&, Universe&);
public:
    UniverseParser() = default;
    UniverseParser(CmdArgs&);

    void Parse(Universe&);
};
