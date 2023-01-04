#include "CmdArgs.hpp"

CmdArgs::CmdArgs(int argc, char* argv[]) {
    const char *optstring = "i:m:f:o:";
    const struct option longopts[] = {
        {"iterations",  optional_argument, NULL, 'i'},
        {"mode",        required_argument, NULL, 'm'},
        {"filename",    optional_argument, NULL, 'f'},
        {"output",      optional_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };
    char opt_char;
    int longindex;
    extern char *optarg;

    try {
        while ((opt_char = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
            switch (opt_char) {
                case 'i': {
                    this->_iterations = std::stoi(optarg);
                    break;
                }
                case 'o': {
                    this->_output_file = optarg;
                    break;
                }
                case 'f': {
                    this->_input_file = optarg;
                    break;
                }
                case 'm': {
                    if (optarg == (std::string) "online") {
                        this->_mode = ONLINE;
                    }
                    else if (optarg == (std::string) "offline") {
                        this->_mode = OFFLINE;
                    }
                    else {
                        throw;
                    }
                    break;
                }
                default: {
                    throw;
                }
            }
        }
    }
    catch (...) {
        throw /*CmdArgsException(
            "Incorrect arguments format",
            (std::string) optarg,
            opt_char
        )*/;
    }
    this->Check();
}

bool CmdArgs::Check() {
    if (this->GetMode() == ONLINE) {
        ;
    }
    else if (this->GetMode() == OFFLINE) {
        if (this->GetInputFile() == "") {
            std::cout << "ex: no input file\n";
            throw;
        }
        if (this->GetOutputFile() == "") {
            std::cout << "ex: no output file\n";
            throw;
        }
        if (this->GetIterations() == -1) {
            std::cout << "ex: no iterations\n";
            throw;
        }
    }
    return true;
}

int CmdArgs::GetIterations() {
    return this->_iterations;
}

std::string& CmdArgs::GetInputFile() {
    return this->_input_file;
}

std::string& CmdArgs::GetOutputFile() {
    return this->_output_file;
}

mode_type CmdArgs::GetMode() {
    return this->_mode;
}

/*
void CmdArgs::SetIterations(int iterations) {
    this->_iterations = iterations;
}

void CmdArgs::SetInputFile(std::string &input_file) {
    this->_input_file = input_file;
}
*/
void CmdArgs::SetOutputFile(std::string &output_file) {
    this->_output_file = output_file;
}
/*
void CmdArgs::SetMode(mode_type mode) {
    this->_mode = mode;
}
*/

std::ostream& operator<<(std::ostream& o, const CmdArgs& args) {
    o << "iterations:   " << args._iterations   << "\n"
      << "input file:   " << args._input_file   << "\n"
      << "output file:  " << args._output_file  << "\n"
      << "mode:         " << args._mode         << "\n";
    return o;
}

