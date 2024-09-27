#ifndef CSVFORMAT_H
#define CSVFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class CSVFormat : public FileFormat {
public:
  // Destructor
  ~CSVFormat() override;

  std::string parse(const std::ifstream &file) const override;

  std::string format(const std::string data) const override;
};

#endif
