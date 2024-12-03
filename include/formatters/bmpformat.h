#ifndef BMPFORMAT_H
#define BMPFORMAT_H

#include "fileformat.h"

class BMPFormat : public FileFormat {
public:
    virtual ~BMPFormat();

    // Override methods for BMP format
    virtual std::vector<uchar> parseBinary(std::ifstream &file) const override;
    virtual std::string formatBinary(const std::vector<uchar> &data,
                                     const std::string &outputFilePath) const override;
};

#endif // BMPFORMAT_H
