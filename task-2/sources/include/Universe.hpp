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
    std::string _name = "Default";
    std::vector<std::vector<Cell>> _field;
public:
    Universe();
    Universe(std::pair<int, int> &size, 
             std::string &name
             ) :
        _size(size), 
        _name(name) {}
 
    std::pair<int, int> GetSize();
    bool IsCellAlive(int x, int y);
    
    void SetName(const std::string&);
    void SetSize(std::pair<int, int> &size);
    void SetCell(int x, int y, bool is_alive);

    std::string GetName();

};
