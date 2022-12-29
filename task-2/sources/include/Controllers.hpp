#include <regex>
#include <iostream>
#include "Cell.hpp"
#include "Universe.hpp"

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
public:
    GameController() = default;
    GameController(Universe &universe, CmdArgs &args) :
        _universe_ptr(&universe), _args_ptr(&args) {}

    void SetUniverse(Universe &universe)    { _universe_ptr = &universe;    }
    void SetArgs    (CmdArgs &args)         { _args_ptr     = &args;        }

    bool IsCellAliveNext(int x, int y);
    std::vector<std::pair<int, int>> GetNextAliveCells();
    void SetFieldFromAliveCoords(std::vector<std::pair<int, int>> &alive_cells);

    void Tick();

    ~GameController() {}
};

class OnlineController : public GameController {
private:
    cmdlinetype GetLineType(std::string&);
public:
    OnlineController() = default;
    OnlineController(Universe &universe, CmdArgs &args) : GameController(universe, args) {}
    void Work();
    void PrintHelp();
};

class OfflineController : public GameController {
private:
    
public:
    OfflineController() = default;
    OfflineController(Universe &universe, CmdArgs &args) : GameController(universe, args) {}

    void Work();
};
