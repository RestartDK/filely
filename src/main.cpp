#include <fstream>
using namespace std;

int main() {
  fstream file;
  string path = "./example.png";

  file.open(path);
}
