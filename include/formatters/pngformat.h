#ifndef PNGFORMAT_H
#define PNGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class PNGFormat : public FileFormat {
public:
  // Destructor
  ~PNGFormat() override;

  std::string parse(std::ifstream &file) const override;

  std::string format(const std::string &data, const std::string &outputFilePath) const override;
};

#endif
