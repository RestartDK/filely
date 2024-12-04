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

  // For formats that handle binary data (e.g., images, BMP)
  virtual std::vector<uchar> parseBinary(std::ifstream &file) const {
    throw BinaryParsingException("Binary parsing not implemented for this file format.");
  }

  virtual std::string formatBinary(const std::vector<uchar> &data,
                                   const std::string &outputFilePath) const {
    throw BinaryFormattingException("Binary formatting not implemented for this file format.");
  }

  // For formats that handle text data (e.g., CSV, JSON, TXT)
  virtual std::string parseText(std::ifstream &file) const {
    throw TextParsingException("Text parsing not implemented for this file format.");
  }

  virtual std::string formatText(const std::string &data,
                                 const std::string &outputFilePath) const {
    throw TextFormattingException("Text formatting not implemented for this file format.");
  }
};

// Custom exception classes
class BinaryParsingException : public std::runtime_error {
public:
  explicit BinaryParsingException(const std::string &msg) : std::runtime_error(msg) {}
};

class BinaryFormattingException : public std::runtime_error {
public:
  explicit BinaryFormattingException(const std::string &msg) : std::runtime_error(msg) {}
};

class TextParsingException : public std::runtime_error {
public:
  explicit TextParsingException(const std::string &msg) : std::runtime_error(msg) {}
};

class TextFormattingException : public std::runtime_error {
public:
  explicit TextFormattingException(const std::string &msg) : std::runtime_error(msg) {}
};

#endif