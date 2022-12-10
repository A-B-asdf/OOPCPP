#include "CmdArgs.hpp"

CmdArgs::CmdArgs(int argc, char* argv[]) {
    const char *optstring = "i:m:f:o:";
    const struct option longopts[] = {
        {"iterations",  required_argument, NULL, 'i'},
        {"mode",        required_argument, NULL, 'm'},
        {"filename",    required_argument, NULL, 'f'},
        {"output",      required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };
    char opt_char;
    int longindex;
    extern char *optarg;

    while ((opt_char = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
        switch (opt_char) {  // todo: сделать обработку ошибки, пример "./task-2/bin/main -i 100500 -f input_lol -o -m 1984"
            case 'i': {
                try {
                    this->_iterations = std::stoi(optarg);
                }
                catch (...) {  // todo
                    throw;
                }
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
                    std::cout << (std::string) "offline" << "\n" << optarg << "\n";
                    throw std::exception();  // todo: exception
                }
                break;
            }
            default: {
                throw std::exception();  // todo: exception
            }
        }
    }
}

int CmdArgs::GetIterations() {
    return this->_iterations;
}

std::string CmdArgs::GetInputFile() {
    return this->_input_file;
}

std::string CmdArgs::GetOutputFile() {
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

void CmdArgs::SetOutputFile(std::string &output_file) {
    this->_output_file = output_file;
}

void CmdArgs::SetMode(mode_type mode) {
    this->_mode = mode;
}
*/

void CmdArgs::SetDefaultInputFile() {
    this->_input_file = "";
}

std::ostream& operator<<(std::ostream& o, const CmdArgs& args) {
    o << "iterations:   " << args._iterations   << "\n"
      << "input file:   " << args._input_file   << "\n"
      << "output file:  " << args._output_file  << "\n"
      << "mode:         " << args._mode         << "\n";
    return o;
}

