#include <getopt.h>
#include <string>
#include <iostream>

typedef enum Modes {
        ONLINE = 0
    ,   OFFLINE
} mode_t;

class CmdArgs {
private:
    int _iterations = 1;
    std::string _input_file = NULL;
    std::string _output_file = NULL;
    mode_t _mode = ONLINE;
public:
    CmdArgs() = default;
    CmdArgs(int argc, char* argv[]);

    int GetIterations();
    std::string GetInputFile();
    std::string GetOutputFile();
    mode_t GetMode();
/*
    void SetIterations(int);
    void SetInputFile(std::string&);
    void SetOutputFile(std::string&);
    void SetMode(mode_t);
*/
    friend std::ostream& operator<<(std::ostream&, const CmdArgs&);
};

std::ostream& operator<<(std::ostream&, const CmdArgs&);
