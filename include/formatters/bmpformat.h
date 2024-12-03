#ifndef BMPFORMAT_H
#define BMPFORMAT_H

#include "fileformat.h"

class BMPFormat : public FileFormat {
public:
    virtual ~BMPFormat();


    virtual std::vector<uchar> parseBinary(std::ifstream &file) const override;
    virtual std::string formatBinary(const std::vector<uchar> &data,
                                     const std::string &outputFilePath) const override;
};

#endif 
