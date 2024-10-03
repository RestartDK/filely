#ifndef CONVERTER_H
#define CONVERTER_H

#include "fileformat.h"
#include <string>

class Converter {
private:
    std::string inputFilePath;
    std::string outputFilePath;
    FileFormat* inputFormat;
    FileFormat* outputFormat;

public:
    Converter(std::string inputFilePath, std::string outputFilePath, FileFormat* inputFormat, FileFormat* outputFormat);

    void convert();
};

#endif
