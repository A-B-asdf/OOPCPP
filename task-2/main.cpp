#include "CmdArgs.hpp"
#include "Universe.hpp"
#include "OnlineController.hpp"
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
            ;
        }
        else {
            ;
        }
    }

    return 0;
}
