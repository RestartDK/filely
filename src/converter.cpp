#include "converter.h"
#include <fstream>
#include <iostream>

Converter::Converter(std::string inputFilePath, std::string outputFilePath, FileFormat* inputFormat, FileFormat* outputFormat)
    : inputFilePath(inputFilePath), outputFilePath(outputFilePath), inputFormat(inputFormat), outputFormat(outputFormat) {}

void Converter::convert() {
    // Open input file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputFilePath);
    }

    // Parse the input file
    std::cout << "Parsing input file: " << inputFilePath << std::endl;
    std::string data = inputFormat->parse(inputFile);
    inputFile.close();

    // Print the parsed data for debugging purposes
    std::cout << "Parsed data:\n" << data << std::endl;

    // Format the data and write to output file
    std::cout << "Formatting data and writing to output file: " << outputFilePath << std::endl;
    std::string result = outputFormat->format(data, outputFilePath);
    
    // Print the result after formatting
    std::cout << result << std::endl;
}
