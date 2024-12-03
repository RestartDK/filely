#include "textformat.h"
#include <iostream>
#include <fstream>
#include <sstream>

TextFormat::~TextFormat() {}

std::string TextFormat::parseText(std::ifstream &file) const {
    std::cout << "Entering TextFormat::parseText" << std::endl;

    // Read the entire file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    std::cout << "Text data parsed successfully." << std::endl;
    return data;
}

std::string TextFormat::formatText(const std::string &data,
                                   const std::string &outputFilePath) const {
    std::cout << "Entering TextFormat::formatText" << std::endl;

    // Write the data to the output file
    std::ofstream outFile(outputFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Failed to open output file: " << outputFilePath << std::endl;
        return "Error: Failed to open output file.";
    }

    outFile << data;
    outFile.close();

    std::cout << "Text data written to file successfully: " << outputFilePath << std::endl;
    return "Text data written to file successfully: " + outputFilePath;
}
