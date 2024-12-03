#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

#include "fileformat.h"

class TextFormat : public FileFormat {
public:
    virtual ~TextFormat();

    virtual std::string parseText(std::ifstream &file) const override;
    virtual std::string formatText(const std::string &data,
                                   const std::string &outputFilePath) const override;
};

#endif 
