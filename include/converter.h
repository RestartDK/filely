#ifndef CONVERTER_H
#define CONVERTER_H

#include "fileformat.h"

class Converter {
private:
  std::string inputFilePath;
  std::string outputFilePath;
  FileFormat *inputFormat;
  FileFormat *outputFormat;

public:
  // Constructor to initialize the converter with the input and output formats
  Converter(std::string inputFilePath, std::string outputFilePath,
            FileFormat *inputFormat, FileFormat *outputFormat);

  void convert();
};

#endif
