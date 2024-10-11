#include "csvformat.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

CSVFormat::~CSVFormat() {}

string CSVFormat::parseText(ifstream &file) const {
  cout << "Entering CSVFormat::parse" << endl;

  // Read the entire CSV file content into a string
  stringstream buffer;
  buffer << file.rdbuf();
  string csvData = buffer.str();

  // Debugging print to show the CSV data
  cout << "CSV data read from file:\n" << csvData << endl;

  return csvData;
}

string CSVFormat::formatText(const string &data,
                             const std::string &outputFilePath) const {
  // This method takes JSON data as input and converts it to CSV format

  // Parse the JSON data
  istringstream dataStream(data);
  string line;
  vector<string> headers;
  vector<vector<string>> rows;
  bool inObject = false;
  map<string, string> keyValues;

  cout << "Formatting JSON to CSV..." << endl;
  cout << "Data before formatting:\n" << data << endl;

  while (getline(dataStream, line)) {
    // Remove leading and trailing whitespace
    line.erase(0, line.find_first_not_of(" \t\n\r"));
    line.erase(line.find_last_not_of(" \t\n\r") + 1);

    if (line == "{" || line == "{\r") {
      inObject = true;
      keyValues.clear();
    } else if (line == "}," || line == "}" || line == "},\r" || line == "}\r") {
      inObject = false;
      // Collect headers
      for (const auto &kv : keyValues) {
        if (find(headers.begin(), headers.end(), kv.first) == headers.end()) {
          headers.push_back(kv.first);
        }
      }
      // Collect values in order of headers
      vector<string> row;
      for (const auto &header : headers) {
        auto it = keyValues.find(header);
        if (it != keyValues.end()) {
          row.push_back(it->second);
        } else {
          row.push_back("");
        }
      }
      rows.push_back(row);
    } else if (inObject) {
      // Parse key-value pair
      size_t colonPos = line.find(":");
      if (colonPos != string::npos) {
        string key = line.substr(0, colonPos);
        string value = line.substr(colonPos + 1);

        // Remove quotes and commas from key
        key.erase(0, key.find_first_not_of(" \t\n\r\""));
        key.erase(key.find_last_not_of(" \t\n\r\",") + 1);

        // Remove quotes and commas from value
        value.erase(0, value.find_first_not_of(" \t\n\r\""));
        value.erase(value.find_last_not_of(" \t\n\r\",") + 1);

        // Store key-value pair
        keyValues[key] = value;
      }
    }
  }

  // Open CSV file for writing
  ofstream outputFile(outputFilePath);
  if (!outputFile.is_open()) {
    return "Error: Unable to open output CSV file.";
  }

  // Write headers to CSV
  for (size_t i = 0; i < headers.size(); ++i) {
    outputFile << headers[i];
    if (i < headers.size() - 1) {
      outputFile << ",";
    }
  }
  outputFile << "\n"; // Newline after headers

  // Write rows to CSV
  for (const auto &row : rows) {
    for (size_t i = 0; i < row.size(); ++i) {
      outputFile << row[i];
      if (i < row.size() - 1) {
        outputFile << ",";
      }
    }
    outputFile << "\n"; // Newline after each row
  }

  // Close the CSV file
  outputFile.close();

  return "CSV file created successfully: " + outputFilePath;
}
