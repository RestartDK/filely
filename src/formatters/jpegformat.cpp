#include "jpegformat.h"
#include <iostream>

JPEGFormat::~JPEGFormat() {
   // Destructor
}

std::vector<uchar> JPEGFormat::parseBinary(std::ifstream &file) const
{
   std::cout << "Entering JPEGFormat::parseBinary" << std::endl;

   // Read the entire file content into a vector
   std::vector<uchar> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

   // Decode the image to ensure it's valid
   cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
   if (image.empty()) {
       std::cerr << "Error: Failed to decode JPEG image." << std::endl;
       return {};
   }

   std::cout << "JPEG image parsed successfully." << std::endl;
   return buffer;
}

std::string JPEGFormat::formatBinary(const std::vector<uchar> &data, const std::string &outputFilePath) const
{
   std::cout << "Entering JPEGFormat::formatBinary" << std::endl;

   // Decode the image
   cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
   if (image.empty()) {
       std::cerr << "Error: Failed to decode image data for JPEG format." << std::endl;
       return "Error: Failed to decode image data for JPEG format.";
   }

   // Write the image to a JPEG file
   if (!cv::imwrite(outputFilePath, image)) {
       std::cerr << "Error: Failed to write JPEG file." << std::endl;
       return "Error: Failed to write JPEG file.";
   }

   std::cout << "JPEG file created successfully: " << outputFilePath << std::endl;
   return "JPEG file created successfully: " + outputFilePath;
}
