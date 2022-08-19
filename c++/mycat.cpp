#include <iostream>
#include <fstream>

#define ERR_ARGS   (1)
#define ERR_FOPEN  (2)

#define VERSION    "0.0.1"

bool printHelp()
{
    std::cout << "USAGE: mycat [files]\n";
    std::cout << "       mycat -n | --lineno [files]\n";
    std::cout << "       mycat -v | --version\n";
    return true;
}

int main(int argc, char **argv)
{
    int i = 1, lineno = 1;
    bool showLinNum = false;
    if (argc < 2) {
        std::cout << "mycat: too few arguments\n";
        printHelp();
        std::exit(ERR_ARGS);
    }
    if (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")) { 
        printHelp();
        exit(0);
    } else if (!std::strcmp(argv[1], "-n") || !std::strcmp(argv[1], "--lineno")) {
        i = 2;
        showLinNum = true;
        if (argc < 3) {
            std::cout << "mycat: too few arguments\n";
            printHelp();
            std::exit(ERR_ARGS);
        }
    } else if (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version")) {
        std::cout << "MyCat Program v" VERSION "\n";
        std::cout << "Authors: Aviruk Basak\n";
        std::cout << "License: MIT\n";
        exit(0);
    }
    for (; i < argc; i++) {
        std::ifstream file = std::ifstream(argv[i]);
        if (!file) {
            std::cout << "mycat: error opening file: file '" << argv[i] << "'\n";
            std::exit(ERR_FOPEN);
        }
        std::string line = "";
        while (getline(file, line)) {
            showLinNum && std::cout << lineno++ << "\t";
            std::cout << line << "\n";
        }
        file.close();
    }
    return 0;
}
