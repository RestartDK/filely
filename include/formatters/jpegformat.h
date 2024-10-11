#ifndef JPEGFORMAT_H
#define JPEGFORMAT_H

#include "fileformat.h"
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>

class JPEGFormat : public FileFormat {
public:

   ~JPEGFormat() override;

   // Parse binary data from the JPEG file
   std::vector<uchar> parseBinary(std::ifstream &file) const override;

   // Format binary data and save it as a JPEG file
   std::string formatBinary(const std::vector<uchar> &data, const std::string &outputFilePath) const override;
};

#endif

