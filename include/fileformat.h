#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdexcept> // For exceptions
#include <string>
#include <vector>

class FileFormat {
public:
  virtual ~FileFormat() {}

  // For formats that handle binary data (e.g., images)
  virtual std::vector<uchar> parseBinary(std::ifstream &file) const {
    throw std::runtime_error(
        "Binary parsing not implemented for this file format.");
  }

  virtual std::string formatBinary(const std::vector<uchar> &data,
                                   const std::string &outputFilePath) const {
    throw std::runtime_error(
        "Binary formatting not implemented for this file format.");
  }

  // For formats that handle text data (e.g., CSV, JSON)
  virtual std::string parseText(std::ifstream &file) const {
    throw std::runtime_error(
        "Text parsing not implemented for this file format.");
  }

  virtual std::string formatText(const std::string &data,
                                 const std::string &outputFilePath) const {
    throw std::runtime_error(
        "Text formatting not implemented for this file format.");
  }
};

#endif
