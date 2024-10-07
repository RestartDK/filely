#include "formatters/pngformat.h"
#include <fstream>
#include <sstream>
using namespace std;

PNGFormat::~PNGFormat() = default;

vector<uchar> PNGFormat::parseBinary(ifstream &file) const {}

string PNGFormat::formatBinary(const vector<uchar> &data,
                               const std::string &outputFilePath) const {
  // Process data here
}
