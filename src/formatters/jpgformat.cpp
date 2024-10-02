#include "formatters/jpgformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JPGFormat::~JPGFormat() = default;

string JPGFormat::parse(const ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string JPGFormat::format(const string data) const {
  // Process data here
  return "Formatted data: " + data;
}
