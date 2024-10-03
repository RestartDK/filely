#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <fstream>
#include <string>

class FileFormat {
public:
    virtual ~FileFormat() {}

    // Parse data from input file stream
    virtual std::string parse(std::ifstream &file) const = 0;

    // Format data and write to output file path
    virtual std::string format(const std::string &data, const std::string &outputFilePath) const = 0;
};

#endif
