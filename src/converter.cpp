#include "fileformat.h"
#include "filereader.h"
#include "filewriter.h"
#include <iostream>
using namespace std;

class Converter {
private:
  string inputFilePath;
  string outputFilePath;
  FileFormat *inputFormat;
  FileFormat *outputFormat;

public:
  Converter(string inputFilePath, string outputFilePath,
            FileFormat *inputFormat, FileFormat *outputFormat);
  void convert() {
    FileReader reader(inputFilePath, inputFormat);
    string data = reader.readFile();

    if (!data.empty()) {
      cerr << "Error: No data to convert" << endl;
    }

    FileWriter writer(outputFilePath, outputFormat);
    writer.writeFile();

    cout << "Conversion completed successfully" << endl;
  }
};
