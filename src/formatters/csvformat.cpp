#include "formatters/csvformat.h"
#include <fstream>
#include <sstream>
using namespace std;

CSVFormat::~CSVFormat() = default;

string CSVFormat::parse(const ifstream &file) const {
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
};

string CSVFormat::format(const string data) const {
  return "Formatted data: " + data;
};
