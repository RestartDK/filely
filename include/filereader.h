#ifndef FILEREADER_H
#define FILEREADER_H

#include "fileformat.h"
#include <string>

class FileReader {
private:
  std::string path;   // Path to the file
  FileFormat *format; // Pointer to a FileFormat object

public:
  FileReader(std::string path, FileFormat *format);

  // Method to read the file using the FileFormat class
  std::string readFile();
};

#endif
