#include "CmdArgs.hpp"
#include "Universe.hpp"
#include "Controllers.hpp"

int main(int argc, char *argv[]) {
    CmdArgs args = CmdArgs(argc, argv);

    Universe universe;
    if (args.GetMode() == ONLINE) {
        UniverseParser parser = UniverseParser(args);
        parser.Parse(universe);
        OnlineController controller = OnlineController();
        controller.Work(universe, args);
    }
    else if (args.GetMode() == OFFLINE) {
        if (args.GetInputFile() == "") {
            std::cout << "No input file, it's nessesary for offline mode";  // ex
        }
        else {
            UniverseParser parser = UniverseParser(args);
            parser.Parse(universe);
            OfflineController controller = OfflineController();
            controller.Work(universe, args);
        }
    }
    return 0;
}
