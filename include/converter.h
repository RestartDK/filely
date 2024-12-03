#ifndef CONVERTER_H
#define CONVERTER_H

#include "fileformat.h"
#include <string>


class Converter {
private:
    const std::string inputFilePath;
    const std::string outputFilePath;
    FileFormat* const inputFormat;
    FileFormat* const outputFormat;

public:
    // Constructor with inline initializer list
    Converter(const std::string& inputPath, const std::string& outputPath,
              FileFormat* const inFormat, FileFormat* const outFormat)
        : inputFilePath(inputPath), outputFilePath(outputPath),
          inputFormat(inFormat), outputFormat(outFormat) {
        if (!inFormat || !outFormat) {
            throw std::invalid_argument("Input or output format cannot be null.");
        }
    }

    void convert(); // Perform the conversion
};

#endif