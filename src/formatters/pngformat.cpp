#include "formatters/pngformat.h"
#include <iostream>
using namespace std;

PNGFormat::~PNGFormat() {}

vector<uchar> PNGFormat::parseBinary(ifstream &file) const {
  cout << "Entering PNGFormat::parseBinary" << endl;

  // Read the entire file content into a vector
  vector<uchar> buffer((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());

  // Decode the image to ensure it's valid
  cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode PNG image." << endl;
    return {};
  }

  cout << "PNG image parsed successfully." << endl;
  return buffer;
}

string PNGFormat::formatBinary(const vector<uchar> &data,
                               const string &outputFilePath) const {
  cout << "Entering PNGFormat::formatBinary" << endl;

  // Decode the image
  cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode image data for PNG format." << endl;
    return "Error: Failed to decode image data for PNG format.";
  }

  // Write the image to a PNG file
  if (!cv::imwrite(outputFilePath, image)) {
    cerr << "Error: Failed to write PNG file." << endl;
    return "Error: Failed to write PNG file.";
  }

  cout << "PNG file created successfully: " << outputFilePath << endl;
  return "PNG file created successfully: " + outputFilePath;
}
