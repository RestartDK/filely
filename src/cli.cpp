#include "cli.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

CLIOptions parseArguments(int argc, char* argv[]) {
    cout << "Starting to parse arguments..." << endl; // Debugging output
    CLIOptions options;

    if (argc < 2) {
        cout << "Not enough arguments provided." << endl; // Debugging output
        options.showHelp = true;
        return options;
    }

    // Initialize the validFormats vector without an initializer list
    vector<string> validFormats;
    validFormats.push_back("png");
    validFormats.push_back("jpg");
    validFormats.push_back("jpeg");
    validFormats.push_back("csv");
    validFormats.push_back("json");

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        cout << "Processing argument: " << arg << endl; // Debugging output
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            return options;
        } else if (arg == "-t") {
            if (i + 1 < argc) {
                options.outputFormat = argv[++i];
                transform(options.outputFormat.begin(), options.outputFormat.end(),
                              options.outputFormat.begin(), ::tolower);
                cout << "Output format detected: " << options.outputFormat << endl; // Debugging output
                if (find(validFormats.begin(), validFormats.end(), options.outputFormat) == validFormats.end()) {
                    cerr << "Error: Unsupported output format '" << options.outputFormat << "'.\n";
                    options.showHelp = true;
                    return options;
                }
            } else {
                cerr << "Error: No output format specified after '-t'.\n";
                options.showHelp = true;
                return options;
            }
        } else if (arg == "-p") {
            if (i + 1 < argc) {
                options.outputPath = argv[++i];
                cout << "Output path detected: " << options.outputPath << endl; // Debugging output
            } else {
                cerr << "Error: No output path specified after '-p'.\n";
                options.showHelp = true;
                return options;
            }
        } else if (arg[0] != '-') {
            options.inputFile = arg;
            cout << "Input file detected: " << options.inputFile << endl; // Debugging output
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

    cout << "Arguments parsed successfully." << endl; // Debugging output
    return options;
}

void displayHelp() {
    cout << "Usage: fc <input_file> -t <output_format> -p <output_path>\n"
              << "Options:\n"
              << "  -t <format>     Specify the output format (png, jpg, jpeg, csv, json)\n"
              << "  -p <path>       Specify the output path\n"
              << "  -h, --help      Display this help message\n";
}
