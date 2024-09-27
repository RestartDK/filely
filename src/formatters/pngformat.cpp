#include "formatters/pngformat.h"
#include <fstream>
#include <sstream>
using namespace std;

PNGFormat::~PNGFormat() = default;

string PNGFormat::parse(const ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string PNGFormat::format(const string data) const {
  // Process data here
  return "Formatted data: " + data;
}
