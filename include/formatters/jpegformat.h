#ifndef JPEGFORMAT_H
#define JPEGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JPEGFormat : public FileFormat {
public:
  // Destructor
  ~JPEGFormat() override;

  std::string parse(std::ifstream &file) const override;

  std::string format(const std::string &data, const std::string &outputFilePath) const override;
};

#endif
