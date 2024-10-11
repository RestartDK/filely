#ifndef CLI_H
#define CLI_H

#include <string>

struct CLIOptions {
    bool showHelp = false;
    std::string inputFile;
    std::string outputFormat;
    std::string outputPath;
    std::string errorMessage;

    bool inputFileProvided = false;
    bool outputFormatProvided = false;
    bool outputPathProvided = false;
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif // CLI_H