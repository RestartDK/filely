#ifndef JPGFORMAT_H
#define JPGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JPGFormat : public FileFormat {
public:
  // Destructor
  ~JPGFormat() override;

  std::vector<uchar> parseBinary(std::ifstream &file) const override;

  std::string formatBinary(const std::vector<uchar> &data,
                           const std::string &outputFilePath) const override;
};

#endif
