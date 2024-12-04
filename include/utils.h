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

// Custom exception class for unsupported file formats
class FileFormatException : public std::exception {
private:
    std::string message_;
public:
    FileFormatException(const std::string& msg) : message_(msg) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};
#endif 