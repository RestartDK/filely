#include "formatters/jpegformat.h"
#include <fstream>
#include <sstream>
using namespace std;

JPEGFormat::~JPEGFormat() = default;

vector<uchar> JPEGFormat::parseBinary(ifstream &file) const {}

string JPEGFormat::formatBinary(const vector<uchar> &data,
                                const std::string &outputFilePath) const {
  // Process data here
}
