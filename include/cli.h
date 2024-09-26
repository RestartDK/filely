#ifndef CLI_H
#define CLI_H

#include <string>

struct CLIOptions {
    std::string inputFile;
    std::string outputFormat;
    bool showHelp = false;
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif 
