#ifndef CSVFORMAT_H
#define CSVFORMAT_H

#include "fileformat.h"

class CSVFormat : public FileFormat {
public:
    std::string parse(const std::string& rawData) const override;
    std::string format(const std::string& structuredData) const override;
};

#endif // CSVFORMAT_H
