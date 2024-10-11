#include "cli.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(x) cout << x << endl;
#else
#define DEBUG_PRINT(x)
#endif

CLIOptions parseArguments(int argc, char* argv[]) {
    CLIOptions options;

    if (argc < 2) {
        DEBUG_PRINT("Not enough arguments provided.");
        options.showHelp = true;
        options.errorMessage = "Error: No arguments provided.";
        return options;
    }

    // List of valid output formats
    vector<string> validFormats = {"png", "jpg", "jpeg", "csv", "json"};

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            return options;
        } else if (arg == "-t") {
            if (options.outputFormatProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Duplicate output format specified.";
                return options;
            }
            if (i + 1 < argc) {
                options.outputFormat = argv[++i];
                options.outputFormatProvided = true;
                transform(options.outputFormat.begin(), options.outputFormat.end(),
                               options.outputFormat.begin(), ::tolower);
                DEBUG_PRINT("Output format detected: " + options.outputFormat);
                if (find(validFormats.begin(), validFormats.end(), options.outputFormat) == validFormats.end()) {
                    options.showHelp = true;
                    options.errorMessage = "Error: Unsupported output format '" + options.outputFormat + "'.";
                    return options;
                }
            } else {
                options.showHelp = true;
                options.errorMessage = "Error: No output format specified after '-t'.";
                return options;
            }
        } else if (arg == "-p") {
            if (options.outputPathProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Duplicate output path specified.";
                return options;
            }
            if (i + 1 < argc) {
                options.outputPath = argv[++i];
                options.outputPathProvided = true;
                DEBUG_PRINT("Output path detected: " + options.outputPath);
            } else {
                options.showHelp = true;
                options.errorMessage = "Error: No output path specified after '-p'.";
                return options;
            }
        } else if (arg[0] != '-') {
            if (options.inputFileProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Multiple input files specified.";
                return options;
            }
            options.inputFile = arg;
            options.inputFileProvided = true;
            DEBUG_PRINT("Input file detected: " + options.inputFile);
        } else {
            // Unknown option encountered
            options.showHelp = true;
            options.errorMessage = "Error: Unknown option '" + arg + "'.";
            return options;
        }
    }

    // Validate required options
    if (!options.inputFileProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No input file specified.";
        return options;
    }
    if (!options.outputFormatProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No output format specified.";
        return options;
    }
    if (!options.outputPathProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No output path specified.";
        return options;
    }

    // Validate input file existence
    ifstream file(options.inputFile);
    if (!file.good()) {
        options.showHelp = true;
        options.errorMessage = "Error: Input file '" + options.inputFile + "' does not exist.";
        return options;
    }
    file.close();

  if (argc < 2) {
    DEBUG_PRINT("Not enough arguments provided.");
    options.showHelp = true;
    options.errorMessage = "Error: No arguments provided.";
    return options;
  }

  // List of valid output formats
  std::vector<std::string> validFormats = {"png", "jpg", "jpeg", "csv", "json"};

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      options.showHelp = true;
      return options;
    } else if (arg == "-t") {
      if (options.outputFormatProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: Duplicate output format specified.";
        return options;
      }
      if (i + 1 < argc) {
        options.outputFormat = argv[++i];
        options.outputFormatProvided = true;
        std::transform(options.outputFormat.begin(), options.outputFormat.end(),
                       options.outputFormat.begin(), ::tolower);
        DEBUG_PRINT("Output format detected: " + options.outputFormat);
        if (std::find(validFormats.begin(), validFormats.end(),
                      options.outputFormat) == validFormats.end()) {
          options.showHelp = true;
          options.errorMessage = "Error: Unsupported output format '" +
                                 options.outputFormat + "'.";
          return options;
        }
      } else {
        options.showHelp = true;
        options.errorMessage = "Error: No output format specified after '-t'.";
        return options;
      }
    } else if (arg == "-p") {
      if (options.outputPathProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: Duplicate output path specified.";
        return options;
      }
      if (i + 1 < argc) {
        options.outputPath = argv[++i];
        options.outputPathProvided = true;
        DEBUG_PRINT("Output path detected: " + options.outputPath);
      } else {
        options.showHelp = true;
        options.errorMessage = "Error: No output path specified after '-p'.";
        return options;
      }
    } else if (arg[0] != '-') {
      if (options.inputFileProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: Multiple input files specified.";
        return options;
      }
      options.inputFile = arg;
      options.inputFileProvided = true;
      DEBUG_PRINT("Input file detected: " + options.inputFile);
    } else {
      // Unknown option encountered
      options.showHelp = true;
      options.errorMessage = "Error: Unknown option '" + arg + "'.";
      return options;
    }
  }

  // Validate required options
  if (!options.inputFileProvided) {
    options.showHelp = true;
    options.errorMessage = "Error: No input file specified.";
    return options;
  }
  if (!options.outputFormatProvided) {
    options.showHelp = true;
    options.errorMessage = "Error: No output format specified.";
    return options;
  }
  if (!options.outputPathProvided) {
    options.showHelp = true;
    options.errorMessage = "Error: No output path specified.";
    return options;
  }

  // Validate input file existence
  std::ifstream file(options.inputFile);
  if (!file.good()) {
    options.showHelp = true;
    options.errorMessage =
        "Error: Input file '" + options.inputFile + "' does not exist.";
    return options;
  }
  file.close();

  return options;
}

void displayHelp() {
    cout << "Usage: file_converter <input_file> -t <output_format> -p <output_path>\n"
              << "Options:\n"
              << "  -t <format>     Specify the output format (png, jpg, jpeg, csv, json)\n"
              << "  -p <path>       Specify the output path\n"
              << "  -h, --help      Display this help message\n";
}
