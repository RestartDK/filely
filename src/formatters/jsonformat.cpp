#include "formatters/jsonformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JSONFormat::~JSONFormat() = default;

string JSONFormat::parse(const ifstream &file) const {
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string JSONFormat::format(const string data) const {
  // Process data here
  return "Formatted data: " + data;
}
