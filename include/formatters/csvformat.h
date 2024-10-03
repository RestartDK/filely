#ifndef CSVFORMAT_H
#define CSVFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class CSVFormat : public FileFormat {
public:
  // Destructor
  ~CSVFormat() override;

  std::string parse(std::ifstream &file) const override;

  std::string format(const std::string &data, const std::string &outputFilePath) const override;
};

#endif