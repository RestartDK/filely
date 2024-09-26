#include "fileformat.h"
#include <fstream>
#include <string>
using namespace std;

class FileReader {
private:
  string path;
  FileFormat *format;

public:
  FileReader(string path, FileFormat *format) : path(path), format(format) {}

  string readFile() {
    // Read file into memory
    ifstream file(path);

    return format->parse(file);
  }
};
