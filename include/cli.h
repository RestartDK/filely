#ifndef CLI_H
#define CLI_H

#include <string>

using namespace std;

struct CLIOptions {
    string inputFile;
    string outputFormat;
    bool showHelp = false;
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif
