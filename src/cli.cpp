#include "cli.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

CLIOptions parseArguments(int argc, char* argv[]) {
    CLIOptions options;

    if (argc < 2) {
        options.showHelp = true;
        return options;
    }

    static const std::vector<std::string> validFormats = {"png", "jpg", "jpeg"};

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            return options;
        } else if (arg == "-t") {
            if (i + 1 < argc) {
                options.outputFormat = argv[++i];
                std::transform(options.outputFormat.begin(), options.outputFormat.end(),
                               options.outputFormat.begin(), ::tolower);
                if (std::find(validFormats.begin(), validFormats.end(), options.outputFormat) == validFormats.end()) {
                    std::cerr << "Error: Unsupported output format '" << options.outputFormat << "'.\n";
                    std::cerr << "Supported formats are: png, jpg, jpeg.\n";
                    options.showHelp = true;
                    return options;
                }
            } else {
                std::cerr << "Error: No output format specified after '-t'.\n";
                options.showHelp = true;
                return options;
            }
        } else if (arg[0] != '-') {
            options.inputFile = arg;
        } else {
            std::cerr << "Error: Unknown option '" << arg << "'.\n";
            options.showHelp = true;
            return options;
        }
    }

    if (options.inputFile.empty()) {
        std::cerr << "Error: No input file specified.\n";
        options.showHelp = true;
        return options;
    }

    std::ifstream file(options.inputFile);
    if (!file.good()) {
        std::cerr << "Error: Input file '" << options.inputFile << "' does not exist.\n";
        options.showHelp = true;
        return options;
    }
    file.close();

    return options;
}

void displayHelp() {
    std::cout << "Usage: fc <input_file> -t <output_format>\n"
              << "Options:\n"
              << "  -t <format>     Specify the output format (png, jpg, jpeg)\n"
              << "  -h, --help      Display this help message\n";
}
