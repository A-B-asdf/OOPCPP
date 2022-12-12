#include <regex>
#include <iostream>

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

#include "Cell.hpp"
#include "Universe.hpp"
#include <algorithm> 

void GameController::Tick(Universe &universe, int tick_count) {  // todo: разбить на файлы
    for (int i = 0; i < tick_count; ++ i) {
        std::vector<std::pair<int, int>> next_alive_cells;
        for (int x = 0; x < universe.RowCount(); ++x) {
            for (int y = 0; y < universe.ColCount(); ++y) {
                if (universe.IsCellAliveNext(x, y)) {
                    next_alive_cells.emplace_back();  // todo: говнокод
                    next_alive_cells.at(next_alive_cells.size() - 1).first = x;
                    next_alive_cells.at(next_alive_cells.size() - 1).second = y;
                }
            }
        }
        for (int x = 0; x < universe.RowCount(); ++x) {
            for (int y = 0; y < universe.ColCount(); ++y) {
                bool is_alive = false;
                for (auto p : next_alive_cells) {
                    if (p.first == x && p.second == y) { // todo: говнокод
                        is_alive = true;
                    }
                }
                universe.SetCell(x, y, is_alive);
            }
        }
        universe.IncreaseIteration(1);
    }
}

class OnlineController : public GameController {
private:
    cmdlinetype GetLineType(std::string&);
public:
    void Work(Universe &);
    void PrintHelp();
};

void OnlineController::Work(Universe &universe) {  //, CmdArgs &args
    std::cout << universe;
    PrintHelp();
    bool break_cmd = false;
    while (!break_cmd) {
        std::string line;
        std::getline(std::cin, line);
        switch (this->GetLineType(line)) {
            case DUMP: {
                std::string filename = line.substr(line.find('<') + 1, line.size() - line.find('<') - 2);
                std::cout << filename << "\n";
                universe.Save2File(filename);
                break;
            }
            case TICK: {
                int tick_count = std::stoi(line.substr(line.find('<') + 3, line.size() - line.find('<') - 4));
                this->Tick(universe, tick_count);
                std::cout << universe;
                break;
            }
            case EXIT:
                std::cout << "Bye!\nc u soon ^ ^\n";
                break_cmd = true;
                break;
            case HELP: {
                this->PrintHelp();
                break;
            }
            default: {
                std::cout << "wtf&\nHere is text that may help u:\n";
                this->PrintHelp();
                break;
            }
        }
    }
    
}

cmdlinetype OnlineController::GetLineType(std::string &line) {
    const std::regex dump_rgx("dump <.+>");
    const std::regex tick_rgx("t(ick)?( <n=\\d+>)?");
    const std::regex exit_rgx("exit");
    const std::regex help_rgx("help");
    if (std::regex_match(line, dump_rgx)) {
        return DUMP;
    } else if (std::regex_match(line, tick_rgx)) {
        return TICK;
    } else if (std::regex_match(line, exit_rgx)) {
        return EXIT;
    } else if (std::regex_match(line, help_rgx)) {
        return HELP;
    } else {
        return UNKNOWN;
    }    
}

void OnlineController::PrintHelp() {
    std::cout
    << "dump <filename> - save world in file" << std::endl
    << "tick <n=1> - tick world n times, default 1" << std::endl
    << "exit - exit from program" << std::endl
    << "help - see this text again ^ ^" << std::endl;
}

class OfflineController : public GameController {
private:
    
public:
    void Work(Universe&, CmdArgs&);
};

void OfflineController::Work(Universe &universe, CmdArgs &args) {
    this->Tick(universe, args.GetIterations());
    universe.Save2File(args.GetOutputFile());
}
