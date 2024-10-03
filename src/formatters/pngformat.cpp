#include "formatters/pngformat.h"
#include <fstream>
#include <sstream>
using namespace std;

PNGFormat::~PNGFormat() = default;

string PNGFormat::parse(ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string PNGFormat::format(const string &data, const std::string &outputFilePath) const {
  // Process data here
  return "Formatted data: " + data;
}
