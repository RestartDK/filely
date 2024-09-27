#include "jsonformat.h"
#include <sstream>
#include <vector>

using namespace std;

string JSONFormat::parse(ifstream &file) const
string JSONFormat::parse(ifstream &file) const
{
    string line;
    vector<string> headers;
    vector<vector<string>> rows;
    bool inObject = false;
    vector<string> row;

    while (getline(file, line))
    {
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        if (line == "{" || line == "{\r")
        {
            inObject = true;
            row.clear();
        }
        else if (line == "}," || line == "}" || line == "},\r" || line == "}\r")
        {
            inObject = false;
            rows.push_back(row);
        }
        else if (inObject)
        {
            // Parse key-value pair
            size_t colonPos = line.find(":");
            if (colonPos != string::npos)
            {
                string key = line.substr(0, colonPos);
                string value = line.substr(colonPos + 1);

                // Remove quotes and commas
                key.erase(0, key.find_first_not_of(" \t\n\r\""));
                key.erase(key.find_last_not_of(" \t\n\r\",") + 1);

                value.erase(0, value.find_first_not_of(" \t\n\r\""));
                value.erase(value.find_last_not_of(" \t\n\r\",") + 1);

                // Add header if not already present
                if (find(headers.begin(), headers.end(), key) == headers.end())
                {
                    headers.push_back(key);
                }

                row.push_back(value);
            }
        }
    }

    // Construct CSV-formatted string
    stringstream csv;

    // Write headers
    for (size_t i = 0; i < headers.size(); ++i)
    {
        csv << headers[i];
        if (i < headers.size() - 1)
        {
            csv << ",";
        }
    }
    csv << "\n";

    // Write rows
    for (const auto &r : rows)
    {
        for (size_t i = 0; i < r.size(); ++i)
        {
            csv << r[i];
            if (i < r.size() - 1)
            {
                csv << ",";
            }
        }
        csv << "\n";
    }

    return csv.str();
}

string JSONFormat::format(ofstream &file, const string &data) const
{
    // Parse the CSV data
    istringstream dataStream(data);
    string line;
    vector<string> headers;
    vector<vector<string>> rows;

    // Read headers
    if (getline(dataStream, line))
    {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ','))
        {
            headers.push_back(item);
        }
    }

    // Read data rows
    while (getline(dataStream, line))
    {
        stringstream ss(line);
        string item;
        vector<string> row;
        while (getline(ss, item, ','))
        {
            row.push_back(item);
        }
        rows.push_back(row);
    }

    // Write JSON to file
    file << "[\n";
    for (size_t i = 0; i < rows.size(); ++i)
    {
        file << "  {\n";
        for (size_t j = 0; j < headers.size(); ++j)
        {
            file << "    \"" << headers[j] << "\": ";
            if (j < rows[i].size())
            {
                file << "\"" << rows[i][j] << "\"";
            }
            else
            {
                file << "\"\"";
            }
            if (j < headers.size() - 1)
            {
                file << ",";
            }
            file << "\n";
        }
        file << "  }";
        if (i < rows.size() - 1)
        {
            file << ",";
        }
        file << "\n";
    }
    file << "]";

    return "Data written to JSON file.";
}