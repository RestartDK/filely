#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <fstream>
#include <string>

class FileFormat {
public:
    virtual ~FileFormat() {}

    // Parses data from input file and returns structured data as a string
    virtual std::string parse(std::ifstream& inputFile) const = 0;

    // Formats structured data from string and writes to output file
    virtual void format(const std::string& data, std::ofstream& outputFil) const = 0;
};

#endif // FILEFORMAT_H
