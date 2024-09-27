#include "csvformat.h"
#include <sstream>
#include <vector>

using namespace std;

string CSVFormat::parse(ifstream &file) const
{
    vector<string> headers;
    vector<vector<string>> rows;
    string line;

    // Read headers
    if (getline(file, line))
    {
        stringstream ss(line);
        string item;
        while (getline(ss, item, ','))
        {
            headers.push_back(item);
        }
    }

    // Read data rows
    while (getline(file, line))
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

    // Construct JSON string
    stringstream json;
    json << "[\n";
    for (size_t i = 0; i < rows.size(); ++i)
    {
        json << "  {\n";
        for (size_t j = 0; j < headers.size(); ++j)
        {
            json << "    \"" << headers[j] << "\": ";
            if (j < rows[i].size())
            {
                json << "\"" << rows[i][j] << "\"";
            }
            else
            {
                json << "\"\"";
            }
            if (j < headers.size() - 1)
            {
                json << ",";
            }
            json << "\n";
        }
        json << "  }";
        if (i < rows.size() - 1)
        {
            json << ",";
        }
        json << "\n";
    }
    json << "]";

    return json.str();
}

string CSVFormat::format(ofstream &file, const string &data) const
{
    // Parse the JSON data
    istringstream dataStream(data);
    string line;
    vector<string> headers;
    vector<vector<string>> rows;
    bool inObject = false;
    vector<string> row;

    while (getline(dataStream, line))
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

    // Write headers
    for (size_t i = 0; i < headers.size(); ++i)
    {
        file << headers[i];
        if (i < headers.size() - 1)
        {
            file << ",";
        }
    }
    file << "\n";

    // Write rows
    for (const auto &r : rows)
    {
        for (size_t i = 0; i < r.size(); ++i)
        {
            file << r[i];
            if (i < r.size() - 1)
            {
                file << ",";
            }
        }
        file << "\n";
    }

    return "Data written to CSV file.";
}