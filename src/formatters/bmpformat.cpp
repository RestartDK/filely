#include "bmpformat.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

BMPFormat::~BMPFormat() {}

std::vector<uchar> BMPFormat::parseBinary(std::ifstream &file) const {
    std::cout << "Entering BMPFormat::parseBinary" << std::endl;

    // Read the entire file content into a vector
    std::vector<uchar> buffer((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());

    // Optionally, validate the image using OpenCV
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cerr << "Error: Failed to decode BMP image." << std::endl;
        return {};
    }

    std::cout << "BMP image parsed successfully." << std::endl;
    return buffer;
}

std::string BMPFormat::formatBinary(const std::vector<uchar> &data,
                                    const std::string &outputFilePath) const {
    std::cout << "Entering BMPFormat::formatBinary" << std::endl;

    // Decode the image data
    cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cerr << "Error: Failed to decode image data for BMP format." << std::endl;
        return "Error: Failed to decode image data for BMP format.";
    }

    // Write the image to a BMP file
    if (!cv::imwrite(outputFilePath, image)) {
        std::cerr << "Error: Failed to write BMP file." << std::endl;
        return "Error: Failed to write BMP file.";
    }

    std::cout << "BMP file created successfully: " << outputFilePath << std::endl;
    return "BMP file created successfully: " + outputFilePath;
}
