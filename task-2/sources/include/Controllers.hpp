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
private:
public:
    void Tick(Universe&, int);
    GameController() {}
    ~GameController() {}
};

class OnlineController : public GameController {
private:
    cmdlinetype GetLineType(std::string&);
public:
    void Work(Universe&, CmdArgs &args);
    void PrintHelp();
};

class OfflineController : public GameController {
private:
    
public:
    void Work(Universe&, CmdArgs&);
};
