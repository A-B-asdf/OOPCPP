#include "Utils.hpp"

void Utils::PrintUniverse(Universe &universe, struct Rules &rules, int iteration) {
    std::cout << "Name: " << universe.GetName() << "\n";
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
    for (int x = 0; x < universe.GetSize().first; ++x) {
        for (int y = 0; y < universe.GetSize().second; ++y) {
            std::cout << ((universe.IsCellAlive(x, y)) ? '*' : '.');
        }
        std::cout << "\n";
    }
}

void Utils::Save2File(Universe &universe, struct Rules &rules, std::string &filename) {
    std::ofstream out;
    out.open(filename, std::ios::out);
    if (!out.is_open()) {
        std::cout << "ex: bad output file\n";
        throw;
    }
    out << "#Life 1.06\n";
    out << "#N " << universe.GetName() << "\n";
    out << "#R B";
    for (int num : rules.born) {
        out << num;
    }
    out << "/S";
    for (int num : rules.stay) {
        out << num;
    }
    out << "\n";
    for (int x = 0; x < universe.GetSize().first; ++x) {
        for (int y = 0; y < universe.GetSize().second; ++y) {
            if (universe.IsCellAlive(x, y)) {
                out << x - universe.GetSize().first / 2 << " " 
                    << y - universe.GetSize().second / 2  << "\n";
            }
        }
    }
    out.close();
}

