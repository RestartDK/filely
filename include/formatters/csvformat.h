#ifndef CSVFORMAT_H
#define CSVFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class CSVFormat : public FileFormat {
public:
  ~CSVFormat() override {}

  std::string parse(std::ifstream &file) const override;

  std::string format(const std::string data) const override;
};

#endif