#ifndef CLI_H
#define CLI_H

#include <string>

using namespace std;

struct CLIOptions {
    bool showHelp = false;
    string inputFile;
    string outputFormat;
    string outputPath;
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif
