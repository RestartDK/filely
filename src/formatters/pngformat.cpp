#include "formatters/pngformat.h"
#include <iostream>

PNGFormat::~PNGFormat() {
  // Destructor
}

std::vector<uchar> PNGFormat::parseBinary(std::ifstream &file) const {
  std::cout << "Entering PNGFormat::parseBinary" << std::endl;

  // Read the entire file content into a vector
  std::vector<uchar> buffer((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

  // Decode the image to ensure it's valid
  cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    std::cerr << "Error: Failed to decode PNG image." << std::endl;
    return {};
  }

  std::cout << "PNG image parsed successfully." << std::endl;
  return buffer;
}

std::string PNGFormat::formatBinary(const std::vector<uchar> &data,
                                    const std::string &outputFilePath) const {
  std::cout << "Entering PNGFormat::formatBinary" << std::endl;

  // Decode the image
  cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    std::cerr << "Error: Failed to decode image data for PNG format."
              << std::endl;
    return "Error: Failed to decode image data for PNG format.";
  }

  // Write the image to a PNG file
  if (!cv::imwrite(outputFilePath, image)) {
    std::cerr << "Error: Failed to write PNG file." << std::endl;
    return "Error: Failed to write PNG file.";
  }

  std::cout << "PNG file created successfully: " << outputFilePath << std::endl;
  return "PNG file created successfully: " + outputFilePath;
}
