#include "cli.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

// Include for terminal colors and formatting
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

// Function to set console text color using conditional compilation
void setConsoleColor(int colorCode) {
#ifdef PLATFORM_WINDOWS
    // Windows console color handling
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#else
    // UNIX terminal color handling
    std::cout << "\033[" << colorCode << "m";
#endif
}

// Function to reset console text color
void resetConsoleColor() {
#ifdef PLATFORM_WINDOWS
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
#else
    std::cout << "\033[0m";
#endif
}

// Function to clear the screen
void clearScreen() {
#ifdef PLATFORM_WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

// Typing animation
void typingAnimation(const std::string &text, int delayMs = 50) {
    for (char c : text) {
        std::cout << c;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::endl;
}

// Expanding animation
void expandingAnimation(const std::string &art, int delayMs = 100) {
    std::istringstream stream(art);
    std::string line;
    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Pulsing animation
void pulsingAnimation(const std::string &art, int pulses = 3, int delayMs = 200) {
    for (int i = 0; i < pulses; ++i) {
#ifdef PLATFORM_WINDOWS
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 11); // Cyan color
#else
        std::cout << "\033[36m"; // Cyan
#endif
        std::cout << art;
        resetConsoleColor();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        std::cout << "\033[2J\033[H"; // Clear screen and move cursor to home position

#ifdef PLATFORM_WINDOWS
        SetConsoleTextAttribute(hConsole, 14); // Yellow color
#else
        std::cout << "\033[33m"; // Yellow
#endif
        std::cout << art;
        resetConsoleColor();
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        std::cout << "\033[2J\033[H"; // Clear screen and move cursor to home position
    }
}

// Function to display the banner with 3D animation
void displayBanner() {
    std::string banner = R"(
███████╗██╗██╗     ███████╗██╗     ██╗   ██╗
██╔════╝██║██║     ██╔════╝██║     ██║   ██║
█████╗  ██║██║     █████╗  ██║     ██║   ██║
██╔══╝  ██║██║     ██╔══╝  ██║     ██║   ██║
██║     ██║███████╗███████╗███████╗╚██████╔╝
╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ 
)";

    std::string slogan = R"(
------------------------------------------------
  FILELY: The Ultimate File Conversion Tool!    
------------------------------------------------
)";

    // Clear screen before animation
    clearScreen();

    // Typing Animation
    setConsoleColor(33); // Yellow
    typingAnimation("Welcome to...", 100);
    resetConsoleColor();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Expanding Animation
    setConsoleColor(36); // Cyan
    expandingAnimation(banner, 100);
    resetConsoleColor();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Pulsing Animation
    pulsingAnimation(banner + slogan, 2, 300);

    // Final display of banner and slogan
    clearScreen();
#ifdef PLATFORM_WINDOWS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11); // Cyan color
#else
    std::cout << "\033[36m"; // Cyan
#endif
    std::cout << banner << std::endl;

#ifdef PLATFORM_WINDOWS
    SetConsoleTextAttribute(hConsole, 14); // Yellow color
#else
    std::cout << "\033[33m"; // Yellow
#endif
    std::cout << slogan << std::endl;
    resetConsoleColor();
}

void displayProgressBar(int progress, int total) {
    int barWidth = 50;
    float ratio = progress / (float)total;
    int pos = barWidth * ratio;

    setConsoleColor(34); // Blue color
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(ratio * 100.0) << " %\r";
    std::cout.flush();
    resetConsoleColor();
}



CLIOptions parseArguments(int argc, char *argv[]) {
    CLIOptions options;

    // If no arguments are provided, switch to interactive mode
    if (argc == 1) {
        clearScreen();
        displayBanner();

        std::string input;
        std::cout << "Welcome to the interactive file converter!\n\n";

        // Step 1: Input File
        setConsoleColor(36); // Cyan color
        std::cout << "Step 1: Specify the input file path\n";
        resetConsoleColor();
        std::cout << "Enter input file path: ";
        std::getline(std::cin, options.inputFile);
        options.inputFileProvided = true;

        // Validate input file existence
        std::ifstream file(options.inputFile);
        while (!file.good()) {
            setConsoleColor(31); // Red color
            std::cout << "Error: Input file does not exist. Please try again.\n";
            resetConsoleColor();
            std::cout << "Enter input file path: ";
            std::getline(std::cin, options.inputFile);
            file.open(options.inputFile);
        }
        file.close();

        setConsoleColor(36); // Cyan color
        std::cout << "\nStep 2: Choose the output format\n";
        resetConsoleColor();
        std::vector<std::string> validFormats = {"png", "jpg", "jpeg", "csv", "json"};

        // Display valid options
        for (size_t i = 0; i < validFormats.size(); ++i) {
            std::cout << i + 1 << ". " << validFormats[i] << "\n";
        }

        // Initialize variables
        int choice = 0;
        bool isFirstAttempt = true; // Flag to differentiate first input attempt

        // Loop until a valid choice is made
        do {
            if (!isFirstAttempt) {
                setConsoleColor(31); // Red color for error message
                std::cout << "Invalid choice. Please select a valid option.\n";
                resetConsoleColor();
            }
            std::cout << "Enter the number corresponding to your choice: ";
            std::cin >> choice;

            // Validate choice
            if (choice >= 1 && choice <= validFormats.size()) {
                break; // Exit loop on valid input
            } else {
                // Invalid input handling
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                isFirstAttempt = false; // Mark as invalid input attempt
            }
        } while (true);

        // Assign the valid choice
        options.outputFormat = validFormats[choice - 1];
        options.outputFormatProvided = true;
        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Step 3: Output Path
        setConsoleColor(36); // Cyan color
        std::cout << "\nStep 3: Specify the output file path\n";
        resetConsoleColor();
        std::cout << "Enter output file path: ";
        std::getline(std::cin, options.outputPath);
        options.outputPathProvided = true;

        // Confirm choices
        setConsoleColor(33); // Yellow color
        std::cout << "\nPlease review your selections:\n";
        resetConsoleColor();
        std::cout << "Input File: " << options.inputFile << "\n";
        std::cout << "Output Format: " << options.outputFormat << "\n";
        std::cout << "Output Path: " << options.outputPath << "\n";

        std::cout << "\nProceed with conversion? (y/n): ";
        char confirm;
        std::cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            options.errorMessage = "Conversion canceled by user.";
            options.showHelp = true;
        }

        return options;
    }

    // Existing command-line argument parsing code
    // List of valid output formats
    std::vector<std::string> validFormats = {"png", "jpg", "jpeg", "csv", "json"};

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            return options;
        } else if (arg == "-t") {
            if (options.outputFormatProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Duplicate output format specified.";
                return options;
            }
            if (i + 1 < argc) {
                options.outputFormat = argv[++i];
                options.outputFormatProvided = true;
                std::transform(options.outputFormat.begin(), options.outputFormat.end(),
                               options.outputFormat.begin(), ::tolower);
                DEBUG_PRINT("Output format detected: " + options.outputFormat);
                if (std::find(validFormats.begin(), validFormats.end(),
                              options.outputFormat) == validFormats.end()) {
                    options.showHelp = true;
                    options.errorMessage = "Error: Unsupported output format '" +
                                           options.outputFormat + "'.";
                    return options;
                }
            } else {
                options.showHelp = true;
                options.errorMessage = "Error: No output format specified after '-t'.";
                return options;
            }
        } else if (arg == "-p") {
            if (options.outputPathProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Duplicate output path specified.";
                return options;
            }
            if (i + 1 < argc) {
                options.outputPath = argv[++i];
                options.outputPathProvided = true;
                DEBUG_PRINT("Output path detected: " + options.outputPath);
            } else {
                options.showHelp = true;
                options.errorMessage = "Error: No output path specified after '-p'.";
                return options;
            }
        } else if (arg[0] != '-') {
            if (options.inputFileProvided) {
                options.showHelp = true;
                options.errorMessage = "Error: Multiple input files specified.";
                return options;
            }
            options.inputFile = arg;
            options.inputFileProvided = true;
            DEBUG_PRINT("Input file detected: " + options.inputFile);
        } else {
            // Unknown option encountered
            options.showHelp = true;
            options.errorMessage = "Error: Unknown option '" + arg + "'.";
            return options;
        }
    }

    // Validate required options
    if (!options.inputFileProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No input file specified.";
        return options;
    }
    if (!options.outputFormatProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No output format specified.";
        return options;
    }
    if (!options.outputPathProvided) {
        options.showHelp = true;
        options.errorMessage = "Error: No output path specified.";
        return options;
    }

    // Validate input file existence
    std::ifstream file(options.inputFile);
    if (!file.good()) {
        options.showHelp = true;
        options.errorMessage =
            "Error: Input file '" + options.inputFile + "' does not exist.";
        return options;
    }
    file.close();

    return options;
}

void displayHelp() {
    setConsoleColor(35); // Magenta color
    std::cout << "\nFile Converter Tool Help\n";
    resetConsoleColor();
    std::cout << "Usage: file_converter <input_file> -t <output_format> -p <output_path>\n"
              << "Options:\n"
              << "  -t <format>     Specify the output format (png, jpg, jpeg, csv, json)\n"
              << "  -p <path>       Specify the output path\n"
              << "  -h, --help      Display this help message\n"
              << "\nIf no arguments are provided, the tool will start in interactive mode.\n";
}
