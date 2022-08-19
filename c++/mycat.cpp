#include <iostream>
#include <fstream>

#define ERR_ARGS (1)
#define VERSION  "0.0.1"

bool printError()
{
    std::cout << "mycat: too few arguments\n";
    std::cout << "USAGE: mycat [files]\n";
    std::cout << "       mycat -n | --lineno [files]\n";
    std::cout << "       mycat -v | --version\n";
    std::exit(ERR_ARGS);
    return true;
}

int main(int argc, char **argv)
{
    int i = 1, lineno = 1;
    bool showLinNum = false;
    argc < 2 && printError();
    if (!std::strcmp(argv[1], "-n") || !std::strcmp(argv[1], "--lineno")) {
        i = 2;
        showLinNum = true;
        argc < 3 && printError();
    } else if (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version")) {
        std::cout << "MyCat Program v" VERSION "\n";
        std::cout << "Authors: Aviruk Basak\n";
        std::cout << "License: MIT\n";
        exit(0);
    }
    for (; i < argc; i++) {
        std::ifstream file(argv[i]);
        std::string line = "";
        while (getline(file, line)) {
            showLinNum && std::cout << lineno++ << "\t";
            std::cout << line << "\n";
        }
    }
    return 0;
}
