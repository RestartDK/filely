#include "converter.h"
#include "fileformat.h"
#include <fstream>
#include <iostream>
using namespace std;

Converter::Converter(string inputFilePath, string outputFilePath,
                     FileFormat *inputFormat, FileFormat *outputFormat){};

ofstream Converter::convert() {
  // Read file parse it with a file format
  ifstream inputFile(inputFilePath);
  string data = inputFormat->parse(inputFile);

  // Error checking for null data
  if (data.empty()) {
    cerr << "Error: No data to convert" << endl;
  }

  // Now format the data and write it to a new file
  string formattedData = outputFormat->format(data);
  ofstream file(data);

  return file;
}
