#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "fileformat.h"
#include <string>

class FileWriter {
private:
  std::string data;   // Raw data of parsed file
  FileFormat *format; // Pointer to a FileFormat object

public:
  FileWriter(std::string data, FileFormat *format);

  // Method to write the file using the FileFormat class
  std::string writeFile();
};

#endif
