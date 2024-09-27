#ifndef JPGFORMAT_H
#define JPGFORMAT_H

#include "fileformat.h"
#include <string>

class JPGFormat : public FileFormat {
public:
  // Destructor
  ~JPGFormat() override;

  std::string parse(const std::ifstream &file) const override;

  std::string format(const std::ofstream &file,
                     const std::string data) const override;
};

#endif
