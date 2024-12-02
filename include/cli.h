#ifndef CLI_H
#define CLI_H

#include <string>

struct CLIOptions {
    bool showHelp;
    std::string inputFile;
    std::string outputFormat;
    std::string outputPath;
    std::string errorMessage;

    bool inputFileProvided;
    bool outputFormatProvided;
    bool outputPathProvided;
    // Default constructor (no parameters)
    CLIOptions()
        : showHelp(false), inputFile(""), outputFormat(""), outputPath(""), errorMessage(""),
          inputFileProvided(false), outputFormatProvided(false), outputPathProvided(false) {}

    // Constructor overloading with basic initialization
    CLIOptions(bool help)
        : showHelp(help), inputFile(""), outputFormat(""), outputPath(""), errorMessage(""),
          inputFileProvided(false), outputFormatProvided(false), outputPathProvided(false) {}

    // Constructor overloading with full initialization
    CLIOptions(bool help, const std::string& input, const std::string& format,
               const std::string& path, const std::string& error = "")
        : showHelp(help), inputFile(input), outputFormat(format), outputPath(path), errorMessage(error),
          inputFileProvided(!input.empty()), outputFormatProvided(!format.empty()), outputPathProvided(!path.empty()) {}
};

CLIOptions parseArguments(int argc, char* argv[]);
void displayHelp();

#endif // CLI_H
