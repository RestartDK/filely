#include "fileformat.h"
#include <fstream>
#include <sstream>
using namespace std;

class CSVFormat : FileFormat {
public:
  string parse(const ifstream &file) const override {
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

  string format(const ofstream &file, const string data) const override {
    // Process data here
    return "Formatted data: " + data;
  }
};
