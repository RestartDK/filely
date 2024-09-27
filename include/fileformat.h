#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <fstream>
#include <string>

class FileFormat {
public:
  virtual ~FileFormat() {}

  // Pure virtual method to parse data from a file stream (input file)
  virtual std::string parse(std::ifstream &file) const = 0;

  // Pure virtual method to format data into a file stream (output file)
  virtual std::string format(std::ofstream &file, const std::string &data) const = 0;
};

#endif