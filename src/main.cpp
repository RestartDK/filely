#include "cli.h"
#include "converter.h"
#include "fileformat.h"
#include "utils.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  CLIOptions options = parseArguments(argc, argv);

  if (options.showHelp) {
    if (!options.errorMessage.empty()) {
      cerr << options.errorMessage << "\n";
    }
    displayHelp();
    return options.inputFile.empty() ? 1 : 0;
  }

  DEBUG_PRINT("Input File: " + options.inputFile);
  DEBUG_PRINT("Output Format: " + options.outputFormat);
  DEBUG_PRINT("Output Path: " + options.outputPath);

  try {
    // Get input format based on input file path
    DEBUG_PRINT("Getting input format...");
    unique_ptr<FileFormat> inputFormat(getFileFormat(options.inputFile));
    if (!inputFormat) {
      cerr << "Error: Unsupported input file format.\n";
      return 1;
    }
    DEBUG_PRINT("Input format successfully determined.");

    // Get output format based on format string
    DEBUG_PRINT("Getting output format...");
    unique_ptr<FileFormat> outputFormat(getFormatFromString(options.outputFormat));
    if (!outputFormat) {
      cerr << "Error: Unsupported output format.\n";
      return 1;
    }
    DEBUG_PRINT("Output format successfully determined.");
    
    DEBUG_PRINT("Starting conversion process...");
    // Perform conversion
    Converter converter(options.inputFile, options.outputPath, inputFormat.get(), outputFormat.get());
    converter.convert();
    DEBUG_PRINT("Conversion process completed successfully.");

  } catch (const FileFormatException &e) {
    cerr << "File format error: " << e.what() << "\n";
    return 1;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    cerr << "An unexpected error occurred.\n";
    return 1;
  }

  return 0;
}