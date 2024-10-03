#include "formatters/jpegformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JPEGFormat::~JPEGFormat() = default;

string JPEGFormat::parse(ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string JPEGFormat::format(const string &data) const {
  // Process data here
  return "Formatted data: " + data;
}
