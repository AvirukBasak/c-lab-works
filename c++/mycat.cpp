#include <iostream>
#include <fstream>

#define ERR_ARGS (1)
#define VERSION  "0.0.1"

bool printHelp()
{
    std::cout << "mycat: too few arguments\n";
    std::cout << "USAGE: mycat [files]\n";
    std::cout << "       mycat -n | --lineno [files]\n";
    std::cout << "       mycat -v | --version\n";
    return true;
}

int main(int argc, char **argv)
{
    int i = 1, lineno = 1;
    bool showLinNum = false;
    bool cinStdin = false;
    if (argc < 2)
        cinStdin = false;
    if (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")) { 
        printHelp();
        exit(0);
    } else if (!std::strcmp(argv[1], "-n") || !std::strcmp(argv[1], "--lineno")) {
        i = 2;
        showLinNum = true;
        argc < 3 && printHelp();
        std::exit(ERR_ARGS);
    } else if (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version")) {
        std::cout << "MyCat Program v" VERSION "\n";
        std::cout << "Authors: Aviruk Basak\n";
        std::cout << "License: MIT\n";
        exit(0);
    }
    for (; i < argc; i++) {
        std::ifstream *file;
        if (cinStdin)
            file = std::cin;
        else
            file = new std::ifstream(argv[i]);
        std::string line = "";
        while (getline(file, line)) {
            showLinNum && std::cout << lineno++ << "\t";
            std::cout << line << "\n";
        }
        if (!cinStdin)
            file.close();
    }
    return 0;
}
