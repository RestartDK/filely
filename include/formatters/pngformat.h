#ifndef PNGFORMAT_H
#define PNGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class PNGFormat : public FileFormat {
public:
  // Destructor
  ~PNGFormat() override;

  std::vector<uchar> parseBinary(std::ifstream &file) const override;

  std::string formatBinary(const std::vector<uchar> &data,
                           const std::string &outputFilePath) const override;
};

#endif
