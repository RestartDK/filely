#include <iostream>
#include "cli.h"

using namespace std;

int main(int argc, char* argv[]) {
  CLIOptions options = parseArguments(argc, argv);

  if (options.showHelp) {
    displayHelp();
    return options.inputFile.empty() ? 1 : 0;
  }

  cout << "Input File: " << options.inputFile << "\n";
  cout << "Output Format: " << options.outputFormat << "\n";

  try {
      // TODO: Implement image conversion logic here
  } catch (const exception& e) {
      cerr << "Error during conversion: " << e.what() << "\n";
      return 1;
  }

  cout << "Conversion completed successfully.\n";
  return 0;
}
