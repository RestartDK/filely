#include "cli.h"
#include "converter.h"
#include "csvformat.h"
#include "fileformat.h"
#include "jpegformat.h"
#include "jpgformat.h"
#include "jsonformat.h"
#include "pngformat.h"
#include <iostream>
#include <string>
using namespace std;

// Add helper funtion to get file format object here!
// TODO: This will be moved somewhere else as a helper function
// or object method
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

    cout << "Input File: " << options.inputFile << "\n";
    cout << "Output Format: " << options.outputFormat << "\n";
    cout << "Output Path: " << options.outputPath << "\n";

  try {
    FileFormat *inputFormat = getFileFormat(options.inputFile);
    FileFormat *outputFormat = getFileFormat(options.outputFormat);
    Converter converter(options.inputFile, options.outputFormat, inputFormat,
                        outputFormat);
    converter.convert();

  } catch (const exception &e) {
    cerr << "Error during conversion: " << e.what() << "\n";
    return 1;
  }
    cout << "Conversion completed successfully.\n";
    return 0;
}
