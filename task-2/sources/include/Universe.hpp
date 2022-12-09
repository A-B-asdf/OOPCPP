#include <string>
#include <vector>
#include <set>
#include "Cell.hpp"

class Universe {
private:
    std::pair<int, int> _size;
    std::set<int> _cells_number_to_born;
    std::set<int> _cells_number_to_stay;
    std::string _name = "Default";
    std::vector<std::vector<Cell>> _field;
public:
    Universe() = default;
    Universe(std::pair<int, int> &size, 
             std::set<int> &cells_number_to_born, 
             std::set<int> &cells_number_to_stay, 
             std::string &name
             ) :
        _size(size), 
        _cells_number_to_born(cells_number_to_born), 
        _cells_number_to_stay(cells_number_to_stay),
        _name(name) {}
    void SetSize(std::pair<int, int> &size);
    void SetRules(const std::set<int>&, const std::set<int>&);
    void SetName(const std::string&);
};


