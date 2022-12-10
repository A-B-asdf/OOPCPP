#include <getopt.h>
#include <string>
#include <iostream>

typedef enum Modes {
        ONLINE
    ,   OFFLINE
} mode_t;

class CmdArgs {
private:
    int _iterations;
    std::string _input_file;
    std::string _output_file;
    mode_t _mode;
public:
    CmdArgs() = default;
    CmdArgs(int argc, char* argv[]);

    int GetIterations();
    std::string GetInputFile();
    std::string GetOutputFile();
    mode_t GetMode();

    void SetIterations(int);
    void SetInputFile(std::string&);
    void SetOutputFile(std::string&);
    void SetMode(mode_t);

    friend std::ostream& operator<<(std::ostream&, const CmdArgs&);
};

std::ostream& operator<<(std::ostream&, const CmdArgs&);
