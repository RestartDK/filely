#include "cli.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

CLIOptions parseArguments(int argc, char* argv[]) {
    CLIOptions options;

    if (argc < 2) {
        options.showHelp = true;
        return options;
    }

    static const vector<string> validFormats = {"png", "jpg", "jpeg"};

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            return options;
        } else if (arg == "-t") {
            if (i + 1 < argc) {
                options.outputFormat = argv[++i];
                transform(options.outputFormat.begin(), options.outputFormat.end(),
                               options.outputFormat.begin(), ::tolower);
                if (find(validFormats.begin(), validFormats.end(), options.outputFormat) == validFormats.end()) {
                    cerr << "Error: Unsupported output format '" << options.outputFormat << "'.\n";
                    cerr << "Supported formats are: png, jpg, jpeg.\n";
                    options.showHelp = true;
                    return options;
                }
            } else {
                cerr << "Error: No output format specified after '-t'.\n";
                options.showHelp = true;
                return options;
            }
        } else if (arg[0] != '-') {
            options.inputFile = arg;
        } else {
            cerr << "Error: Unknown option '" << arg << "'.\n";
            options.showHelp = true;
            return options;
        }
    }

    if (options.inputFile.empty()) {
        cerr << "Error: No input file specified.\n";
        options.showHelp = true;
        return options;
    }

    ifstream file(options.inputFile);
    if (!file.good()) {
        cerr << "Error: Input file '" << options.inputFile << "' does not exist.\n";
        options.showHelp = true;
        return options;
    }
    file.close();

    return options;
}

void displayHelp() {
    cout << "Usage: fc <input_file> -t <output_format>\n"
              << "Options:\n"
              << "  -t <format>     Specify the output format (png, jpg, jpeg)\n"
              << "  -h, --help      Display this help message\n";
}
