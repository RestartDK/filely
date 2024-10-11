#include "jsonformat.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

JSONFormat::~JSONFormat() {}

string JSONFormat::parseText(ifstream &file) const {
  cout << "Entering JSONFormat::parse" << endl;

  // Read the entire JSON file content into a string
  stringstream buffer;
  buffer << file.rdbuf();
  string jsonData = buffer.str();

  // Debugging print to show the JSON data
  cout << "JSON data read from file:\n" << jsonData << endl;

  return jsonData;
}

string JSONFormat::formatText(const string &data,
                              const std::string &outputFilePath) const {
  // Parse the CSV data
  istringstream dataStream(data);
  string line;
  vector<string> headers;
  vector<vector<string>> rows;

  cout << "Formatting CSV to JSON..." << endl; // Debugging print
  cout << "Data before formatting:\n"
       << data << endl; // Print the data received

  // Read headers (first line in the CSV)
  if (getline(dataStream, line)) {
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
      headers.push_back(item); // Store the header columns
    }
  } else {
    return "Error: CSV data is empty or missing headers.";
  }

  // Read the rest of the data rows
  while (getline(dataStream, line)) {
    stringstream ss(line);
    string item;
    vector<string> row;
    while (getline(ss, item, ',')) {
      row.push_back(item); // Store each row
    }

    // Ensure the row has the same number of columns as headers
    if (row.size() != headers.size()) {
      return "Error: Mismatch between number of headers and data columns.";
    }

    rows.push_back(row);
  }

  // Open a JSON file for writing using outputFilePath
  ofstream outputFile(outputFilePath);

  if (!outputFile.is_open()) {
    return "Error: Unable to open output JSON file.";
  }

  // Build the JSON output
  outputFile << "[\n"; // Start of the JSON array

  for (size_t i = 0; i < rows.size(); ++i) {
    outputFile << "  {\n"; // Start of the JSON object for a row

    for (size_t j = 0; j < headers.size(); ++j) {
      // Trim whitespace from headers and values
      string header = headers[j];
      string value = rows[i][j];
      header.erase(header.find_last_not_of(" \t\n\r") + 1);
      header.erase(0, header.find_first_not_of(" \t\n\r"));
      value.erase(value.find_last_not_of(" \t\n\r") + 1);
      value.erase(0, value.find_first_not_of(" \t\n\r"));

      // Escape special characters in header and value
      header = escapeJSON(header);
      value = escapeJSON(value);

      outputFile << "    \"" << header << "\": \"" << value << "\"";

      if (j < headers.size() - 1) {
        outputFile
            << ","; // Add a comma between key-value pairs except the last one
      }

      outputFile << "\n";
    }

    outputFile << "  }";

    if (i < rows.size() - 1) {
      outputFile << ","; // Add a comma between objects except the last one
    }

    outputFile << "\n";
  }

  outputFile << "]"; // End of the JSON array

  // Close the JSON file
  outputFile.close();

  return "JSON file created successfully: " + outputFilePath;
}

// Helper function to escape JSON strings
string JSONFormat::escapeJSON(const string &input) const {
  string output;
  for (char c : input) {
    switch (c) {
    case '\"':
      output += "\\\"";
      break;
    case '\\':
      output += "\\\\";
      break;
    case '\b':
      output += "\\b";
      break;
    case '\f':
      output += "\\f";
      break;
    case '\n':
      output += "\\n";
      break;
    case '\r':
      output += "\\r";
      break;
    case '\t':
      output += "\\t";
      break;
    default:
      output += c;
      break;
    }
  }
  return output;
}
