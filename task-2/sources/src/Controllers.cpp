#include "Controllers.hpp"

#include <algorithm> 

void GameController::Tick(Universe &universe, int tick_count) {
    for (int i = 0; i < tick_count; ++ i) {
        std::vector<std::pair<int, int>> next_alive_cells = universe.GetNextAliveCells();
        universe.SetFieldFromAliveCoords(next_alive_cells);
        universe.IncreaseIteration(1);
    }
}

void OnlineController::Work(Universe &universe, CmdArgs &args) {
    std::cout << universe;
    PrintHelp();
    bool break_cmd = false;
    while (!break_cmd) {
        std::string line;
        std::getline(std::cin, line);
        switch (this->GetLineType(line)) {
            case DUMP: {
                if (line.find('<') != std::string::npos) {
                    std::string output_file = DEFAULT_OUTPUT_DIR + line.substr(line.find('<') + 1, line.size() - line.find('<') - 2);
                    args.SetOutputFile(output_file);
                }
                if (args.GetOutputFile().size() == 0) {
                    std::cout << "Incorrect output file ^ ^";
                }
                std::cout << "Universe 'll be saved into file \"" << args.GetOutputFile() << "\" ^ ^\n";
                universe.Save2File(args.GetOutputFile());
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

void OfflineController::Work(Universe &universe, CmdArgs &args) {
    this->Tick(universe, args.GetIterations());
    universe.Save2File(args.GetOutputFile());
}
