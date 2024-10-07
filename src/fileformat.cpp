#include <fstream>
#include <string>
using namespace std;

class FileFormat
{
public:
  virtual ~FileFormat() {}

  // Will be inherited by children classes to parse into raw data
  virtual string parse(const ifstream &file) const = 0;

  // Will be inherited by children classes to format raw data into a new format
  virtual string format(const ofstream &file, const string data) const = 0;
};
