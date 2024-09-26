#ifndef PNGFORMAT_H
#define PNGFORMAT_H

#include "fileformat.h"
#include <string>

class PNGFormat : public FileFormat {
public:
  // Destructor
  ~PNGFormat() override;

  std::string parse(const std::ifstream &file) const override;

  std::string format(const std::ofstream &file,
                     const std::string data) const override;
};

#endif
