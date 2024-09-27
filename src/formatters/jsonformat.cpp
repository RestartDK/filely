#include "jsonformat.h"
#include <sstream>
#include <vector>

std::string JSONFormat::parse(const std::string& rawData) const {
    // Parses a JSON-like string and converts it into a CSV-like string
    std::istringstream stream(rawData);
    std::ostringstream csvData;
    char ch;
    std::string value;
    bool inString = false;

    while (stream.get(ch)) {
        if (ch == '\"') {
            inString = !inString;
            if (!inString) {
                csvData << value;
                value.clear();
            }
        } else if (ch == ',' && !inString) {
            csvData << ',';
        } else if (ch == '[' || ch == ']' || ch == ' ' || ch == '\n' || ch == '\r') {
            if (ch == ']') {
                csvData << '\n';
            }
            // Ignore other whitespace characters
        } else {
            if (inString) {
                value += ch;
            }
        }
    }

    return csvData.str();
}

std::string JSONFormat::format(const std::string& structuredData) const {
    // Converts CSV-like structured data back into a JSON-like string
    std::istringstream stream(structuredData);
    std::ostringstream jsonData;
    std::string line;

    jsonData << "[";
    bool firstLine = true;
    while (std::getline(stream, line)) {
        if (!firstLine) {
            jsonData << ",";
        }
        jsonData << "[";
        std::istringstream lineStream(line);
        std::string cell;
        bool firstCell = true;
        while (std::getline(lineStream, cell, ',')) {
            if (!firstCell) {
                jsonData << ",";
            }
            jsonData << "\"" << cell << "\"";
            firstCell = false;
        }
        jsonData << "]";
        firstLine = false;
    }
    jsonData << "]";

    return jsonData.str();
}
