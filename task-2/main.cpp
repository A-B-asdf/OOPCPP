#include "CmdArgs.hpp"

int main(int argc, char *argv[]) {
    // parse cmd args
    CmdArgs args = CmdArgs(argc, argv);
    std::cout << args;
    // create the universe
    //Universe universe = Universe();  
    // add rules, initial alive cells

    
    if (args.GetMode() == ONLINE) {
        std::cout << "online mode\n";
    }
    else if (args.GetMode() == OFFLINE) {
        std::cout << "offline mode\n";
    }

    return 0;
}