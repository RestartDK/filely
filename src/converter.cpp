#include "converter.h"
#include "jpgformat.h"
#include "pngformat.h"
#include "jpegformat.h"
#include <fstream>
#include <iostream>

Converter::Converter(std::string inputFilePath, std::string outputFilePath, FileFormat* inputFormat, FileFormat* outputFormat)
    : inputFilePath(inputFilePath), outputFilePath(outputFilePath), inputFormat(inputFormat), outputFormat(outputFormat) {}

void Converter::convert() {
    // Determine if the input and output formats handle binary data
    bool inputIsBinary = false;
    bool outputIsBinary = false;

    // Check if input format is binary (images)
    if (dynamic_cast<PNGFormat*>(inputFormat) != nullptr ||
        dynamic_cast<JPGFormat*>(inputFormat) != nullptr ||
        dynamic_cast<JPEGFormat*>(inputFormat) != nullptr) {
        inputIsBinary = true;
    }

    // Check if output format is binary (images)
    if (dynamic_cast<PNGFormat*>(outputFormat) != nullptr ||
        dynamic_cast<JPGFormat*>(outputFormat) != nullptr ||
        dynamic_cast<JPEGFormat*>(outputFormat) != nullptr) {
        outputIsBinary = true;
    }

    // Open input file with appropriate mode
    std::ifstream inputFile;
    if (inputIsBinary) {
        inputFile.open(inputFilePath, std::ios::binary);
    } else {
        inputFile.open(inputFilePath);
    }

    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputFilePath);
    }

    // Parse the input file
    std::cout << "Parsing input file: " << inputFilePath << std::endl;

    if (inputIsBinary) {
        // Parse binary data
        std::vector<uchar> data = inputFormat->parseBinary(inputFile);
        inputFile.close();

        if (data.empty()) {
            throw std::runtime_error("Failed to parse binary input file.");
        }

        // Print the parsed data size for debugging
        std::cout << "Parsed binary data size: " << data.size() << " bytes" << std::endl;

        if (outputIsBinary) {
            // Format binary data to binary output
            std::cout << "Formatting binary data to binary output file: " << outputFilePath << std::endl;
            std::string result = outputFormat->formatBinary(data, outputFilePath);
            std::cout << result << std::endl;
        } else {
            // Conversion from binary to text (Not implemented)
            std::cerr << "Error: Conversion from binary to text format is not supported." << std::endl;
            throw std::runtime_error("Conversion from binary to text format is not supported.");
        }
    } else {
        // Parse text data
        std::string data = inputFormat->parseText(inputFile);
        inputFile.close();

        if (data.empty()) {
            throw std::runtime_error("Failed to parse text input file.");
        }

        // Print the parsed data for debugging
        std::cout << "Parsed text data:\n" << data << std::endl;

        if (outputIsBinary) {
            // Conversion from text to binary (Not implemented)
            std::cerr << "Error: Conversion from text to binary format is not supported." << std::endl;
            throw std::runtime_error("Conversion from text to binary format is not supported.");
        } else {
            // Format text data to text output
            std::cout << "Formatting text data to text output file: " << outputFilePath << std::endl;
            std::string result = outputFormat->formatText(data, outputFilePath);
            std::cout << result << std::endl;
        }
    }
}
