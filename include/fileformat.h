#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <string>

class FileFormat {
public:
    virtual ~FileFormat() {}

    // Pure virtual function to parse raw data and return structured data
    virtual std::string parse(const std::string& rawData) const = 0;

    // Pure virtual function to format structured data back into specific format
    virtual std::string format(const std::string& structuredData) const = 0;
};

#endif // FILEFORMAT_H
