#include "CmdArgs.hpp"
#include "Universe.hpp"

int main(int argc, char *argv[]) {
    // parse cmd args
    CmdArgs args = CmdArgs(argc, argv);
    std::cout << args;

    Universe universe;
    if (args.GetMode() == ONLINE) {
        std::cout << "online mode\n";
        UniverseParser parser = UniverseParser(args);
        parser.Parse(universe);
        std::cout << universe;
    }
    else if (args.GetMode() == OFFLINE) {
        std::cout << "offline mode\n";
        if (args.GetInputFile() == "") {
            ;
        }
        else {
            ;
        }
    }

    return 0;
}