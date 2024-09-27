
#include "fileformat.h"
#include <fstream>
#include <string>
using namespace std;

class FileWriter {
private:
  string data;
  FileFormat *format;

public:
  FileWriter(string data, FileFormat *format) : data(data), format(format) {}

  string writeFile() {
    // Read raw data from the file
    ofstream file(data);

    // Use the format class to parse the raw data
    return format->format(file, data);
  }
};
