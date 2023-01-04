#include "CmdArgs.hpp"
#include "Universe.hpp"
#include "UniverseParser.hpp"
#include "Controllers.hpp"

int main(int argc, char *argv[]) {
    CmdArgs args = CmdArgs(argc, argv);

    Universe universe;
    if (args.GetMode() == ONLINE) {
        UniverseParser parser = UniverseParser(args.GetInputFile());
        OnlineController controller = OnlineController(universe, args);
        parser.ParseFromFile(universe, controller);
        controller.Work();
    }
    else if (args.GetMode() == OFFLINE) {
        if (args.GetInputFile() == "") {
            std::cout << "No input file, it's nessesary for offline mode";
        }
        if (args.GetOutputFile() == "") {
            std::cout << "No output file, it's nessesary for offline mode";
        }
        if (args.GetIterations() == -1) {
            std::cout << "No iterations, it's nessesary for offline mode";
        }
        else {
            UniverseParser parser = UniverseParser(args.GetInputFile());
            OfflineController controller = OfflineController(universe, args);
            parser.ParseFromFile(universe, controller);
            controller.Work();
        }
    }
    return 0;
}
