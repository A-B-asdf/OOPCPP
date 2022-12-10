#include "CmdArgs.hpp"

CmdArgs::CmdArgs(int argc, char* argv[]) {
    const char *optstring = "hi:m:f:o:";

    const struct option longopts[] = {
        {"iterations",  required_argument, NULL, 'i'},
        {"mode",        required_argument, NULL, 'm'},
        {"filename",    required_argument, NULL, 'f'},
        {"output",      required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    int option;
    int longindex;
    while ((option = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
        switch (option) {
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
                this->_mode = std::stoi(optarg);
                break;
            }
            default: {
                throw std::exception();  // todo: exception
            }
        }
    }
}


