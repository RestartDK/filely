#include "formatters/jpgformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JPGFormat::~JPGFormat() = default;

vector<uchar> JPGFormat::parseBinary(ifstream &file) const {}

string JPGFormat::formatBinary(const vector<uchar> &data,
                               const std::string &outputFilePath) const {
  // Process data here
}
