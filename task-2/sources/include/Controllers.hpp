#include <regex>
#include <fstream>
#include <iostream>
#include "Cell.hpp"
#include "Universe.hpp"

#pragma once

typedef enum CMDLineTypes {
        DUMP = 0
    ,   TICK
    ,   EXIT
    ,   HELP

    ,   UNKNOWN = -1
} cmdlinetype;

class GameController {
protected:
    Universe* _universe_ptr;
    CmdArgs* _args_ptr;
    struct Rules {
        std::set<int> born;
        std::set<int> stay;
    } _rules;
    int _iteration = 0;
public:
    GameController() = default;
    GameController(Universe &universe, CmdArgs &args) :
        _universe_ptr(&universe), _args_ptr(&args) {}

    void SetUniverse(Universe &universe)    { _universe_ptr = &universe;    }
    void SetArgs    (CmdArgs &args)         { _args_ptr     = &args;        }
    void AddNumber2Born(const int);
    void AddNumber2Stay(const int);

    bool IsCellAliveNext(int x, int y);
    std::vector<std::pair<int, int>> GetNextAliveCells();
    void SetFieldFromAliveCoords(std::vector<std::pair<int, int>> &alive_cells);

    void Tick();

    void Print();
    void Save2File(std::string &filename);

    ~GameController() {}
};

class OnlineController : public GameController {
private:
    cmdlinetype GetLineType(std::string&);
    void PrintHelp();
public:
    OnlineController() = default;
    OnlineController(Universe &universe, CmdArgs &args) : GameController(universe, args) {}
    void Work();
};

class OfflineController : public GameController {
public:
    OfflineController() = default;
    OfflineController(Universe &universe, CmdArgs &args) : GameController(universe, args) {}

    void Work();
};
