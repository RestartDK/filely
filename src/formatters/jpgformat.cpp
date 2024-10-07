#include "formatters/jpgformat.h"
#include <iostream>

JPGFormat::~JPGFormat() {
  // Destructor
}

std::vector<uchar> JPGFormat::parseBinary(std::ifstream &file) const {
  std::cout << "Entering JPGFormat::parseBinary" << std::endl;

  // Read the entire file content into a vector
  std::vector<uchar> buffer((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

  // Decode the image to ensure it's valid
  cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    std::cerr << "Error: Failed to decode JPG image." << std::endl;
    return {};
  }

  std::cout << "JPG image parsed successfully." << std::endl;
  return buffer;
}

std::string JPGFormat::formatBinary(const std::vector<uchar> &data,
                                    const std::string &outputFilePath) const {
  std::cout << "Entering JPGFormat::formatBinary" << std::endl;

  // Decode the image
  cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    std::cerr << "Error: Failed to decode image data for JPG format."
              << std::endl;
    return "Error: Failed to decode image data for JPG format.";
  }

  // Write the image to a JPG file
  if (!cv::imwrite(outputFilePath, image)) {
    std::cerr << "Error: Failed to write JPG file." << std::endl;
    return "Error: Failed to write JPG file.";
  }

  std::cout << "JPG file created successfully: " << outputFilePath << std::endl;
  return "JPG file created successfully: " + outputFilePath;
}
