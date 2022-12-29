#include "CmdArgs.hpp"
#include "Universe.hpp"
#include "UniverseParser.hpp"
#include "Controllers.hpp"

int main(int argc, char *argv[]) {
    CmdArgs args = CmdArgs(argc, argv);

    Universe universe;
    if (args.GetMode() == ONLINE) {
        UniverseParser parser = UniverseParser(args);
        OnlineController controller = OnlineController(universe, args);
        parser.Parse(universe, controller);
        controller.Work();
    }
    else if (args.GetMode() == OFFLINE) {
        if (args.GetInputFile() == "") {
            std::cout << "No input file, it's nessesary for offline mode";  // ex
        }
        else {
            UniverseParser parser = UniverseParser(args);
            OfflineController controller = OfflineController(universe, args);
            parser.Parse(universe, controller);
            controller.Work();
        }
    }
    return 0;
}
