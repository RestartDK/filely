#ifndef FILEFORMAT_H // Include guard to prevent multiple inclusions
#define FILEFORMAT_H

#include <fstream>
#include <string>

class FileFormat {
public:
  // Virtual destructor for proper cleanup in derived classes
  virtual ~FileFormat() {}

  // Pure virtual method to parse data from a file stream (input file)
  virtual std::string parse(const std::ifstream &file) const = 0;

  // Pure virtual method to format data into a file stream (output file)
  virtual std::string format(const std::ofstream &file,
                             const std::string data) const = 0;
};

#endif
