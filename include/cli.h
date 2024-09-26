#ifndef CLI_H
#define CLI_H

#include <string>

using namespace std;

struct CLIOptions {
    bool showHelp = false;
    std::string inputFile;
    std::string outputFormat;
    std::string outputPath;
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif
