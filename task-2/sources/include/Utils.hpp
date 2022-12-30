#include "Universe.hpp"
#include <fstream>
#pragma once

class Utils {
public:
    void PrintUniverse(Universe *_universe_ptr, struct Rules &rules, int iteration) {
        std::cout << "Name: " << _universe_ptr->GetName() << "\n";
        std::cout << "Rules: B";
        for (int num : rules.born) {
            std::cout << num;
        }
        std::cout << "/S";
        for (int num : rules.stay) {
            std::cout << num;
        }
        std::cout << "\n";
        std::cout << "Iteration: " << iteration << "\n";
        for (int x = 0; x < _universe_ptr->GetSize().first; ++x) {
            for (int y = 0; y < _universe_ptr->GetSize().second; ++y) {
                std::cout << ((_universe_ptr->IsCellAlive(x, y)) ? '*' : '.');
            }
            std::cout << "\n";
        }
    }

    void Save2File(Universe *_universe_ptr, struct Rules &rules, std::string &filename) {
    std::ofstream out;
    out.open(filename, std::ios::out);
    if (!out.is_open()) {
        std::cout << "ex: bad output file\n";
        throw;
    }
    out << "#Life 1.06\n";
    out << "#N " << _universe_ptr->GetName() << "\n";
    out << "#R B";
    for (int num : rules.born) {
        out << num;
    }
    out << "/S";
    for (int num : rules.stay) {
        out << num;
    }
    out << "\n";
    for (int x = 0; x < _universe_ptr->GetSize().first; ++x) {
        for (int y = 0; y < _universe_ptr->GetSize().second; ++y) {
            if (_universe_ptr->IsCellAlive(x, y)) {
                out << x - _universe_ptr->GetSize().first / 2 << " " 
                    << y - _universe_ptr->GetSize().second / 2  << "\n";
            }
        }
    }
    out.close();
    }

};

