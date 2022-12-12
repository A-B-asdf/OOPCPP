#include <getopt.h>
#include <string>
#include <iostream>
#include <vector>

#pragma once

typedef enum Modes {
        ONLINE = 0
    ,   OFFLINE
} mode_type;

class CmdArgs {
private:
    int _iterations = -1;
    std::string _input_file = "";
    std::string _output_file = "";
    mode_type _mode = ONLINE;
    
    bool Check();

public:
    CmdArgs() = default;
    CmdArgs(int argc, char* argv[]);

    int GetIterations();
    std::string& GetInputFile();
    std::string& GetOutputFile();
    mode_type GetMode();

    //void SetIterations(int);
    //void SetInputFile(std::string&);
    void SetOutputFile(std::string&);
    //void SetMode(mode_type);

    friend std::ostream& operator<<(std::ostream&, const CmdArgs&);
};

std::ostream& operator<<(std::ostream&, const CmdArgs&);
