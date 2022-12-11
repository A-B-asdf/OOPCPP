typedef enum CMDLineTypes {
        DUMP = 0
    ,   TICK
    ,   EXIT
    ,   HELP

    ,   UNKNOWN = -1
} cmdlinetype;

/*
dump <filename> - сохранить вселенную в файл
    tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат. На экране перед распечатанным полем должно отображаться имя вселенной, правило перехода и номер текущей итерации.
    exit – завершить игру
    help – распечатать справку о командах
*/

class OnlineController {
private:
    mdlinetype GetLineType(std::string&);
public:
    OnlineController(/* args */);
    void Work();
    ~OnlineController();
};

