#include "cli.h"
#include "converter.h"
#include "fileformat.h"
#include "formatters/csvformat.h"
#include "formatters/jpegformat.h"
#include "formatters/jpgformat.h"
#include "formatters/jsonformat.h"
#include "formatters/pngformat.h"
#include <iostream>
#include <string>
using namespace std;

// Add helper funtion to get file format object here!
// TODO: This will be moved somewhere else as a helper function
// or object method

FileFormat* getFormatFromString(const std::string& format) {
    if (format == "csv") {
        return new CSVFormat();
    } else if (format == "json") {
        return new JSONFormat();
    } else if (format == "png") {
        return new PNGFormat();
    } else if (format == "jpeg") {
        return new JPEGFormat();
    } else if (format == "jpg") {
        return new JPGFormat();
    }

    std::cerr << "Unsupported output format: " << format << std::endl;
    return nullptr;
}

string getFileExtension(const string &fileName) {
  size_t pos = fileName.find_last_of('.');
  if (pos != string::npos) {
    return fileName.substr(pos + 1); // Return the extension (without the dot)
  }
  return "";
}

FileFormat *getFileFormat(string path) {
  string fileType = getFileExtension(path);

  if (fileType == "csv") {
    return new CSVFormat();
  } else if (fileType == "json") {
    return new JSONFormat();
  } else if (fileType == "png") {
    return new PNGFormat();
  } else if (fileType == "jpeg") {
    return new JPEGFormat();
  } else if (fileType == "jpg") {
    return new JPGFormat();
  }

  cerr << "Unsupported file format: " << endl;
  return nullptr;
}


int main(int argc, char *argv[]) {
    CLIOptions options = parseArguments(argc, argv);

    if (options.showHelp) {
        displayHelp();
        return options.inputFile.empty() ? 1 : 0;
    }

    std::cout << "Input File: " << options.inputFile << "\n";
    std::cout << "Output Format: " << options.outputFormat << "\n";
    std::cout << "Output Path: " << options.outputPath << "\n";

    try {
        FileFormat *inputFormat = getFileFormat(options.inputFile);
        if (!inputFormat) {
            std::cerr << "Error: Unsupported input file format.\n";
            return 1;
        }

        FileFormat *outputFormat = getFormatFromString(options.outputFormat);
        if (!outputFormat) {
            std::cerr << "Error: Unsupported output format.\n";
            return 1;
        }

        Converter converter(options.inputFile, options.outputPath, inputFormat, outputFormat);

        converter.convert();

        // Clean up
        delete inputFormat;
        delete outputFormat;

    } catch (const std::exception &e) {
        std::cerr << "Error during conversion: " << e.what() << "\n";
        return 1;
    }
    std::cout << "Conversion completed successfully.\n";
    return 0;
}
