#include "formatters/jpgformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JPGFormat::~JPGFormat() = default;

string JPGFormat::parse(ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string JPGFormat::format(const string &data, const std::string &outputFilePath) const {
  // Process data here
  return "Formatted data: " + data;
}
