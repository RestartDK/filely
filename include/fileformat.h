#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

class FileFormat {
public:
    virtual ~FileFormat() {}

    // For formats that handle binary data (e.g., images)
    virtual std::vector<uchar> parseBinary(std::ifstream &file) const { return {}; }
    virtual std::string formatBinary(const std::vector<uchar> &data, const std::string &outputFilePath) const { return "Not implemented"; }

    // For formats that handle text data (e.g., CSV, JSON)
    virtual std::string parseText(std::ifstream &file) const { return ""; }
    virtual std::string formatText(const std::string &data, const std::string &outputFilePath) const { return "Not implemented"; }
};

#endif
