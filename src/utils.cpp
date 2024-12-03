#include "utils.h"
#include "formatters/csvformat.h"
#include "formatters/jpegformat.h"
#include "formatters/jpgformat.h"
#include "formatters/jsonformat.h"
#include "formatters/pngformat.h"
#include "formatters/bmpformat.h"     // Added for BMP support
#include "formatters/textformat.h"    // Added for Text support
#include <iostream>
using namespace std;

string getFileExtension(const string &fileName) {
    size_t pos = fileName.find_last_of('.');
    if (pos != string::npos) {
        string extension = fileName.substr(pos + 1);
        DEBUG_PRINT("getFileExtension: Extracted extension: " + extension);
        return extension;
    }
    DEBUG_PRINT("getFileExtension: No extension found!");
    return "";
}

FileFormat* getFileFormat(const string &path) {
    DEBUG_PRINT("getFileFormat: Determining file format for: " + path);
    string fileType = getFileExtension(path);
    DEBUG_PRINT("getFileFormat: File extension detected: " + fileType);

    if (fileType == "csv") {
        DEBUG_PRINT("getFileFormat: Returning CSVFormat object");
        return new CSVFormat();
    } else if (fileType == "json") {
        DEBUG_PRINT("getFileFormat: Returning JSONFormat object");
        return new JSONFormat();
    } else if (fileType == "png") {
        DEBUG_PRINT("getFileFormat: Returning PNGFormat object");
        return new PNGFormat();
    } else if (fileType == "jpeg") {
        DEBUG_PRINT("getFileFormat: Returning JPEGFormat object");
        return new JPEGFormat();
    } else if (fileType == "jpg") {
        DEBUG_PRINT("getFileFormat: Returning JPGFormat object");
    return new JPGFormat();
    } else if (fileType == "bmp") {
        DEBUG_PRINT("getFileFormat: Returning BMPFormat object");
        return new BMPFormat(); // Added for BMP
    } else if (fileType == "txt") {
        DEBUG_PRINT("getFileFormat: Returning TextFormat object");
        return new TextFormat(); // Added for Text
    }

    cerr << "getFileFormat: Unsupported file format: " << fileType << endl;
    return nullptr;
}

FileFormat* getFormatFromString(const string& format) {
    DEBUG_PRINT("Determining output format for: " + format);
    if (format == "csv") {
        return new CSVFormat();
    } else if (format == "json") {
        return new JSONFormat();
    } else if (format == "png") {
        return new PNGFormat();
    } else if (format == "jpeg") {
        return new JPEGFormat();
    } else if (format == "jpg") {
        return new JPGFormat();
    } else if (format == "bmp") {
        return new BMPFormat(); // Added for BMP
    } else if (format == "txt") {
        return new TextFormat(); // Added for Text
    }

    cerr << "Unsupported output format: " << format << endl;
    return nullptr;
}
