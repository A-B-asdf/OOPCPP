#include "Controllers.hpp"

#include <algorithm> 
#include <chrono>
#include <thread>

void GameController::AddNumber2Born(const int a) {
    this->_rules.born.insert(a);
}

void GameController::AddNumber2Stay(const int a) {
    this->_rules.stay.insert(a);
}

void GameController::SetRules(struct Rules &rules) {
    this->_rules = rules;
}

bool GameController::IsCellAliveNext(int x, int y) {
    int sum = 0;
    if (_universe_ptr->IsCellAlive(x    , y - 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x    , y + 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x - 1, y    )) ++sum;
    if (_universe_ptr->IsCellAlive(x - 1, y - 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x - 1, y + 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x + 1, y    )) ++sum;
    if (_universe_ptr->IsCellAlive(x + 1, y + 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x + 1, y - 1)) ++sum;
    if (_universe_ptr->IsCellAlive(x, y)) {
        for (int n : this->_rules.stay) {
            if (n == sum) {
                return true;
            }
        }
        return false;
    }
    else {
        for (int n : this->_rules.born) {
            if (n == sum) {
                return true;
            }
        }
        return false;
    }
}

std::vector<std::pair<int, int>> GameController::GetNextAliveCells() {
    std::vector<std::pair<int, int>> next_alive_cells;
    for (int x = 0; x < _universe_ptr->GetSize().first; ++x) {
        for (int y = 0; y < _universe_ptr->GetSize().second; ++y) {
            if (this->IsCellAliveNext(x, y)) {
                next_alive_cells.emplace_back();
                next_alive_cells.at(next_alive_cells.size() - 1).first  = x - _universe_ptr->GetSize().first  / 2;
                next_alive_cells.at(next_alive_cells.size() - 1).second = y - _universe_ptr->GetSize().second / 2;
            }
        }
    }
    return next_alive_cells;
}

void GameController::Tick() {
    std::vector<std::pair<int, int>> next_alive_cells = GetNextAliveCells();
    _universe_ptr->SetFieldFromAliveCoords(next_alive_cells);
    ++_iteration;
}

void OnlineController::Work() {
    _utils_ptr->PrintUniverse(*_universe_ptr, _rules, _iteration);
    PrintHelp();
    bool break_cmd = false;
    while (!break_cmd) {
        std::string line;
        std::getline(std::cin, line);
        switch (this->GetLineType(line)) {
            case DUMP: {
                if (line.find('<') != std::string::npos) {
                    std::string output_file = (std::string) DEFAULT_OUTPUT_DIR + line.substr(line.find('<') + 1, line.size() - line.find('<') - 2);
                    _args_ptr->SetOutputFile(output_file);
                }
                if (_args_ptr->GetOutputFile().size() == 0) {
                    std::cout << "Incorrect output file ^ ^";
                }
                std::cout << "Universe 'll be saved into file \"" << _args_ptr->GetOutputFile() << "\" ^ ^\n";
                _utils_ptr->Save2File(*_universe_ptr, _rules, _args_ptr->GetOutputFile());
                break;
            }
            case TICK: {
                int tick_count = 1;
                if (line.find('<') != std::string::npos) {
                    tick_count = std::stoi(line.substr(line.find('<') + 3, line.size() - line.find('<') - 4));
                }
                for (int i = 0; i < tick_count; ++i) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    Tick();
                    _utils_ptr->PrintUniverse(*_universe_ptr, _rules, _iteration);
                }
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
                std::cout << "Idk wym _;;\nHere is text that may help u:\n";
                this->PrintHelp();
                break;
            }
        }
    }
    
}

cmdlinetype OnlineController::GetLineType(std::string &line) {
    const std::regex dump_rgx("dump( <.+>)?");
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

void OfflineController::Work() {
    for (int i = 0; i < _args_ptr->GetIterations(); ++i) {
        Tick();
    }
    std::string filename = (std::string) DEFAULT_OUTPUT_DIR + _args_ptr->GetOutputFile();
    _utils_ptr->Save2File(*_universe_ptr, _rules, filename);
}
