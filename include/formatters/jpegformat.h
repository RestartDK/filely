#ifndef JPEGFORMAT_H
#define JPEGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JPEGFormat : public FileFormat {
public:
  // Destructor
  ~JPEGFormat() override;

  std::vector<uchar> parseBinary(std::ifstream &file) const override;

  std::string formatBinary(const std::vector<uchar> &data,
                           const std::string &outputFilePath) const override;
};

#endif
