#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "fileformat.h"

// Debugging macro
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

// Function declarations
std::string getFileExtension(const std::string &fileName);
FileFormat* getFileFormat(const std::string &path);
FileFormat* getFormatFromString(const std::string& format);

#endif 