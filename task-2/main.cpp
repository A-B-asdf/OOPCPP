#include "CmdArgs.hpp"
#include "Universe.hpp"
#include "Controllers.hpp"
/*
int WaitForCommands() {
    
    dump <filename> - сохранить вселенную в файл
    tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат. На экране перед распечатанным полем должно отображаться имя вселенной, правило перехода и номер текущей итерации.
    exit – завершить игру
    help – распечатать справку о командах
    std::string line;
    std::getline(std::cin, line);
    switch (GetType(line)) {
    case 0:
        
        break;
    
    default:
        break;
    }
}*/

int main(int argc, char *argv[]) {
    // parse cmd args
    CmdArgs args = CmdArgs(argc, argv);

    Universe universe;
    if (args.GetMode() == ONLINE) {
        UniverseParser parser = UniverseParser(args);
        parser.Parse(universe);
        OnlineController controller = OnlineController();
        controller.Work(universe);
    }
    else if (args.GetMode() == OFFLINE) {
        if (args.GetInputFile() == "") {
            std::cout << "No input file, it's nessesary for offline mode";
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
