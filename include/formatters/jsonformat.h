#ifndef JSONFORMAT_H
#define JSONFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JSONFormat : public FileFormat {
public:
  // Destructor
  ~JSONFormat() override;

  std::string parse(const std::ifstream &file) const override;

  std::string format(const std::string data) const override;
};

#endif
