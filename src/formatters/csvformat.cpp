#include "csvformat.h"
#include <sstream>
#include <vector>

std::string CSVFormat::parse(const std::string& rawData) const {
    // Parses CSV data and converts it into a simple JSON-like string
    std::vector<std::vector<std::string>> data;
    std::istringstream stream(rawData);
    std::string line;

    while (std::getline(stream, line)) {
        std::vector<std::string> row;
        std::string cell;
        std::istringstream lineStream(line);

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    // Convert the data into a JSON-like string
    std::ostringstream jsonData;
    jsonData << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        jsonData << "[";
        for (size_t j = 0; j < data[i].size(); ++j) {
            jsonData << "\"" << data[i][j] << "\"";
            if (j < data[i].size() - 1) {
                jsonData << ",";
            }
        }
        jsonData << "]";
        if (i < data.size() - 1) {
            jsonData << ",";
        }
    }
    jsonData << "]";

    return jsonData.str();
}

std::string CSVFormat::format(const std::string& structuredData) const {
    // Expects structuredData in a simple JSON-like string format
    // Converts it back to CSV format
    std::istringstream stream(structuredData);
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
            // Ignore these characters
        } else if (ch == ',' && inString) {
            value += ch;
        } else if (ch == ']' && !inString) {
            csvData << '\n';
        } else {
            if (inString) {
                value += ch;
            }
        }
    }

    return csvData.str();
}
