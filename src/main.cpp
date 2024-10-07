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

string getFileExtension(const string &fileName) {
    size_t pos = fileName.find_last_of('.');
    if (pos != string::npos) {
        string extension = fileName.substr(pos + 1);
        cout << "getFileExtension: Extracted extension: " << extension << endl; // Debugging output
        return extension;
    }
    cout << "getFileExtension: No extension found!" << endl; // Debugging output
    return "";
}


// Function to get FileFormat based on file path
FileFormat *getFileFormat(string path) {
    cout << "getFileFormat: Determining file format for: " << path << endl; // Debugging output

    string fileType = getFileExtension(path);
    cout << "getFileFormat: File extension detected: " << fileType << endl; // Debugging output

    if (fileType == "csv") {
        cout << "getFileFormat: Returning CSVFormat object" << endl; // Debugging output
        return new CSVFormat();
    } else if (fileType == "json") {
        cout << "getFileFormat: Returning JSONFormat object" << endl; // Debugging output
        return new JSONFormat();
    } else if (fileType == "png") {
        cout << "getFileFormat: Returning PNGFormat object" << endl; // Debugging output
        return new PNGFormat();
    } else if (fileType == "jpeg") {
        cout << "getFileFormat: Returning JPEGFormat object" << endl; // Debugging output
        return new JPEGFormat();
    } else if (fileType == "jpg") {
        cout << "getFileFormat: Returning JPGFormat object" << endl; // Debugging output
        return new JPGFormat();
    }

    cerr << "getFileFormat: Unsupported file format: " << fileType << endl; // Debugging output
    return nullptr;
}


// Function to get FileFormat based on format string
FileFormat* getFormatFromString(const std::string& format) {
    cout << "Determining output format for: " << format << endl; // Debugging output
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

int main(int argc, char *argv[]) {
    cout << "Program started!" << endl; // Debugging output
    CLIOptions options = parseArguments(argc, argv);

    if (options.showHelp) {
        cout << "Displaying help..." << endl;
        displayHelp();
        return options.inputFile.empty() ? 1 : 0;
    }

    cout << "Input File: " << options.inputFile << "\n";
    cout << "Output Format: " << options.outputFormat << "\n";
    cout << "Output Path: " << options.outputPath << "\n";

    try {
        // Get input format based on input file path
        cout << "Getting input format..." << endl;
        FileFormat *inputFormat = getFileFormat(options.inputFile);
        if (!inputFormat) {
            cerr << "Error: Unsupported input file format.\n";
            return 1;
        }
        cout << "Input format successfully determined." << endl;

        // Get output format based on format string
        cout << "Getting output format..." << endl;
        FileFormat *outputFormat = getFormatFromString(options.outputFormat);
        if (!outputFormat) {
            cerr << "Error: Unsupported output format.\n";
            return 1;
        }
        cout << "Output format successfully determined." << endl;

        // Create Converter and perform conversion
        cout << "Creating converter object..." << endl;
        Converter converter(options.inputFile, options.outputPath, inputFormat, outputFormat);

        cout << "Starting conversion process..." << endl;
        converter.convert();
        cout << "Conversion completed successfully." << endl;

        // Clean up
        delete inputFormat;
        delete outputFormat;

    } catch (const exception &e) {
        cerr << "Error during conversion: " << e.what() << "\n";
        return 1;
    }

    cout << "Program completed successfully." << endl;
    return 0;
}
