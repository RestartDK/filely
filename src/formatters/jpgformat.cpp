#include "formatters/jpgformat.h"
#include <iostream>
using namespace std;

JPGFormat::~JPGFormat() {
  // Destructor
}

vector<uchar> JPGFormat::parseBinary(ifstream &file) const {
  cout << "Entering JPGFormat::parseBinary" << endl;

  // Read the entire file content into a vector
  vector<uchar> buffer((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());

  // Decode the image to ensure it's valid
  cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode JPG image." << endl;
    return {};
  }

  cout << "JPG image parsed successfully." << endl;
  return buffer;
}

string JPGFormat::formatBinary(const vector<uchar> &data,
                               const string &outputFilePath) const {
  cout << "Entering JPGFormat::formatBinary" << endl;

  // Decode the image
  cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode image data for JPG format." << endl;
    return "Error: Failed to decode image data for JPG format.";
  }

  // Write the image to a JPG file
  if (!cv::imwrite(outputFilePath, image)) {
    cerr << "Error: Failed to write JPG file." << endl;
    return "Error: Failed to write JPG file.";
  }

  cout << "JPG file created successfully: " << outputFilePath << endl;
  return "JPG file created successfully: " + outputFilePath;
}
