#include "converter.h"
#include "jpegformat.h"
#include "jpgformat.h"
#include "pngformat.h"
#include <fstream>
#include <iostream>
using namespace std;

using namespace std;

Converter::Converter(string inputFilePath, string outputFilePath, FileFormat* inputFormat, FileFormat* outputFormat)
    : inputFilePath(inputFilePath), outputFilePath(outputFilePath), inputFormat(inputFormat), outputFormat(outputFormat) {}

void Converter::convert() {
  // Determine if the input and output formats handle binary data
  bool inputIsBinary = false;
  bool outputIsBinary = false;

  // Check if input format is binary (images)
  if (dynamic_cast<PNGFormat *>(inputFormat) != nullptr ||
      dynamic_cast<JPGFormat *>(inputFormat) != nullptr ||
      dynamic_cast<JPEGFormat *>(inputFormat) != nullptr) {
    inputIsBinary = true;
  }

  // Check if output format is binary (images)
  if (dynamic_cast<PNGFormat *>(outputFormat) != nullptr ||
      dynamic_cast<JPGFormat *>(outputFormat) != nullptr ||
      dynamic_cast<JPEGFormat *>(outputFormat) != nullptr) {
    outputIsBinary = true;
  }

  // Open input file with appropriate mode
  ifstream inputFile;
  if (inputIsBinary) {
    inputFile.open(inputFilePath, ios::binary);
  } else {
    inputFile.open(inputFilePath);
  }

  if (!inputFile.is_open()) {
    throw runtime_error("Failed to open input file: " + inputFilePath);
  }

  // Parse the input file
  cout << "Parsing input file: " << inputFilePath << endl;

  if (inputIsBinary) {
    // Parse binary data
    vector<uchar> data = inputFormat->parseBinary(inputFile);
    inputFile.close();

    if (data.empty()) {
      throw runtime_error("Failed to parse binary input file.");
    }

    // Print the parsed data size for debugging
    cout << "Parsed binary data size: " << data.size() << " bytes" << endl;

    if (outputIsBinary) {
      // Format binary data to binary output
      cout << "Formatting binary data to binary output file: " << outputFilePath
           << endl;
      string result = outputFormat->formatBinary(data, outputFilePath);
      cout << result << endl;
    } else {
      // Conversion from binary to text (Not implemented)
      cerr << "Error: Conversion from binary to text format is not supported."
           << endl;
      throw runtime_error(
          "Conversion from binary to text format is not supported.");
    }
  } else {
    // Parse text data
    string data = inputFormat->parseText(inputFile);
    inputFile.close();

    if (data.empty()) {
      throw runtime_error("Failed to parse text input file.");
    }

    // Print the parsed data for debugging
    cout << "Parsed text data:\n" << data << endl;

    if (outputIsBinary) {
      // Conversion from text to binary (Not implemented)
      cerr << "Error: Conversion from text to binary format is not supported."
           << endl;
      throw runtime_error(
          "Conversion from text to binary format is not supported.");
    } else {
      // Format text data to text output
      cout << "Formatting text data to text output file: " << outputFilePath
           << endl;
      string result = outputFormat->formatText(data, outputFilePath);
      cout << result << endl;
    }
  }
}
