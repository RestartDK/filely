#ifndef JSONFORMAT_H
#define JSONFORMAT_H

#include "fileformat.h"
#include <fstream>
#include <string>

class JSONFormat : public FileFormat {
public:
  // Destructor
  ~JSONFormat() override;

  std::string parseText(std::ifstream &file) const override;

  std::string formatText(const std::string &data, const std::string &outputFilePath) const override;

private:
  // Method to escape special characters in JSON strings
  std::string escapeJSON(const std::string &input) const;
};

#endif
