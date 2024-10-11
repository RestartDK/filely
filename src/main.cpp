#include "cli.h"
#include "converter.h"
#include "fileformat.h"
#include <iostream>
#include <string>
#include "formatters/csvformat.h"
#include "formatters/jpegformat.h"
#include "formatters/jpgformat.h"
#include "formatters/jsonformat.h"
#include "formatters/pngformat.h"

// Debugging macro
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

// Helper functions remain in main.cpp
std::string getFileExtension(const std::string &fileName) {
    size_t pos = fileName.find_last_of('.');
    if (pos != std::string::npos) {
        std::string extension = fileName.substr(pos + 1);
        DEBUG_PRINT("getFileExtension: Extracted extension: " + extension);
        return extension;
    }
    DEBUG_PRINT("getFileExtension: No extension found!");
    return "";
}

FileFormat* getFileFormat(const std::string &path) {
    DEBUG_PRINT("getFileFormat: Determining file format for: " + path);
    std::string fileType = getFileExtension(path);
    DEBUG_PRINT("getFileFormat: File extension detected: " + fileType);

    if (fileType == "csv") {
        DEBUG_PRINT("getFileFormat: Returning CSVFormat object");
        return new CSVFormat();
    } else if (fileType == "json") {
        DEBUG_PRINT("getFileFormat: Returning JSONFormat object");
        return new JSONFormat();
    } else if (fileType == "png") {
        DEBUG_PRINT("getFileFormat: Returning PNGFormat object");
        return new PNGFormat();
    } else if (fileType == "jpeg") {
        DEBUG_PRINT("getFileFormat: Returning JPEGFormat object");
        return new JPEGFormat();
    } else if (fileType == "jpg") {
        DEBUG_PRINT("getFileFormat: Returning JPGFormat object");
        return new JPGFormat();
    }

    std::cerr << "getFileFormat: Unsupported file format: " << fileType << std::endl;
    return nullptr;
}

FileFormat* getFormatFromString(const std::string& format) {
    DEBUG_PRINT("Determining output format for: " + format);
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
    CLIOptions options = parseArguments(argc, argv);

    if (options.showHelp) {
        if (!options.errorMessage.empty()) {
            std::cerr << options.errorMessage << "\n";
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
        std::unique_ptr<FileFormat> inputFormat(getFileFormat(options.inputFile));
        if (!inputFormat) {
            std::cerr << "Error: Unsupported input file format.\n";
            return 1;
        }
        DEBUG_PRINT("Input format successfully determined.");

        // Get output format based on format string
        DEBUG_PRINT("Getting output format...");
        std::unique_ptr<FileFormat> outputFormat(getFormatFromString(options.outputFormat));
        if (!outputFormat) {
            std::cerr << "Error: Unsupported output format.\n";
            return 1;
        }
        DEBUG_PRINT("Output format successfully determined.");

        // Create Converter and perform conversion
        DEBUG_PRINT("Creating converter object...");
        Converter converter(options.inputFile, options.outputPath, inputFormat.get(), outputFormat.get());

        DEBUG_PRINT("Starting conversion process...");
        converter.convert();
        DEBUG_PRINT("Conversion completed successfully.");

    } catch (const std::exception &e) {
        std::cerr << "Error during conversion: " << e.what() << "\n";
        return 1;
    }

    DEBUG_PRINT("Program completed successfully.");
    return 0;
}