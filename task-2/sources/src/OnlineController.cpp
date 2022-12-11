#include "OnlineController.hpp"

void OnlineController::Work() {
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        switch (this->GetLineType(line))
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
    
}

cmdlinetype OnlineController::GetLineType(std::string &line) {
    const std::regex dump_rgx("dump .+");
    const std::regex tick_rgx("t(ick)? (<n=\\d+>)?");
    const std::regex exit_rgx("exit");
    const std::regex help_rgx("help");
    if (std::regex_match(line, dump_regex)) {
        return DUMP;
    } else if (std::regex_match(line, tick_regex)) {
        return TICK;
    } else if (std::regex_match(line, exit_regex)) {
        return EXIT;
    } else if (std::regex_match(line, help_regex)) {
        return HELP;
    } else {
        return UNKNOWN;
    }
    
}
