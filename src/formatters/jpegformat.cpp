#include "jpegformat.h"
#include <iostream>
using namespace std;

JPEGFormat::~JPEGFormat() {}

vector<uchar> JPEGFormat::parseBinary(ifstream &file) const {
  cout << "Entering JPEGFormat::parseBinary" << endl;

  // Read the entire file content into a vector
  vector<uchar> buffer((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());

  // Decode the image to ensure it's valid
  cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode JPEG image." << endl;
    return {};
  }

  cout << "JPEG image parsed successfully." << endl;
  return buffer;
}

string JPEGFormat::formatBinary(const vector<uchar> &data,
                                const string &outputFilePath) const {
  cout << "Entering JPEGFormat::formatBinary" << endl;

  // Decode the image
  cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    cerr << "Error: Failed to decode image data for JPEG format." << endl;
    return "Error: Failed to decode image data for JPEG format.";
  }

  // Write the image to a JPEG file
  if (!cv::imwrite(outputFilePath, image)) {
    cerr << "Error: Failed to write JPEG file." << endl;
    return "Error: Failed to write JPEG file.";
  }

  cout << "JPEG file created successfully: " << outputFilePath << endl;
  return "JPEG file created successfully: " + outputFilePath;
}
