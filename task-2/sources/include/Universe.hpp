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

struct Rules {
    std::set<int> born;
    std::set<int> stay;
};

class Universe {
private:
    std::pair<int, int> _size = {60, 100};
    std::string _name = "Default";
    std::vector<std::vector<Cell>> _field;
public:
    Universe();
    Universe(std::pair<int, int> &size, 
             std::string &name
             ) :
        _size(size), 
        _name(name) {}
 
    bool IsCellAlive(int x, int y);
    
    void SetName(const std::string&);
    void SetSize(std::pair<int, int> &size);
    void SetCell(int x, int y, bool is_alive);
    void SetFieldFromAliveCoords(std::vector<std::pair<int, int>> &alive_cells);

    std::string GetName();
    std::pair<int, int> GetSize();

};
