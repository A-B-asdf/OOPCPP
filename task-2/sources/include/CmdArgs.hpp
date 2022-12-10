#include <getopt.h>
#include <string>

class CmdArgs {
private:
    int _iterations;
    std::string _input_file;
    std::string _output_file;
    int _mode;
public:
    CmdArgs() = default;
    CmdArgs(int argc, char* argv[]);

    int GetIterations();
    std::string GetInputFile();
    std::string GetOutputFile();
    int GetMode();

    int SetIterations();
    std::string SetInputFile();
    std::string SetOutputFile();
    int SetMode();
};
