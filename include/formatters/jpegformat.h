#ifndef JPEGFORMAT_H
#define JPEGFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JPEGFormat : public FileFormat {
public:
  // Destructor
  ~JPEGFormat() override;

  std::string parse(const std::ifstream &file) const override;

  std::string format(const std::string data) const override;
};

#endif
