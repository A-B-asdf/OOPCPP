#pragma once

#include "Universe.hpp"
#include <fstream>

class Utils {
public:
    void PrintUniverse(Universe &, struct Rules &, int );
    void Save2File(Universe &, struct Rules &, std::string &);
};
