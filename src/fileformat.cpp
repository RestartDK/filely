#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class FileFormat {
public:
  virtual ~FileFormat() {}

  // Will be inherited by children classes to parse into raw data
  virtual std::string parseText(std::ifstream &file) const = 0;
  virtual std::string parseBinary(std::ifstream &file) const = 0;

  // Will be inherited by children classes to format raw data into a new format
  virtual std::string formatText(const std::string &data,
                                 const std::string &outputFilePath) const = 0;
  virtual std::string formatBinary(const std::vector<uchar> &data,
                                   const std::string &outputFilePath) const = 0;
};
