#include <gtest/gtest.h>
#include "cli.h"
#include "utils.h"
#include "formatters/jpegformat.h"
#include "formatters/pngformat.h"
#include <fstream>
#include <cstdio>
#include <memory>

const char* PATH = "input.svg";

// NoArguments
TEST(CLIArgumentTest, NoArguments) {
    int argc = 1;
    char* argv[] = {(char*)"file_converter"};
    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
}

// HelpArgument
TEST(CLIArgumentTest, HelpArgument) {
    int argc = 2;
    char* argv[] = {(char*)"file_converter", (char*)"--help"};
    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
}

// ValidArguments
TEST(CLIArgumentTest, ValidArguments) {
    int argc = 6;
    char* argv[] = {
        (char*)"file_converter",
        (char*)PATH,
        (char*)"-t",
        (char*)"jpeg",
        (char*)"-p",
        (char*)"output.jpeg"
    };

    // Create a temporary input file
    std::ofstream outfile(PATH);
    outfile.close();

    // Parse arguments
    CLIOptions options = parseArguments(argc, argv);
    EXPECT_FALSE(options.showHelp);
    EXPECT_EQ(options.inputFile, PATH);
    EXPECT_EQ(options.outputFormat, "jpeg");
    EXPECT_EQ(options.outputPath, "output.jpeg");

    // Verify getFormatFromString functionality
    std::unique_ptr<FileFormat> outputFormat(getFormatFromString(options.outputFormat));
    ASSERT_NE(outputFormat, nullptr) << "Unsupported output file format.";

    // Check that the outputFormat is of the expected type
    if (options.outputFormat == "jpeg") {
        ASSERT_NE(dynamic_cast<JPEGFormat*>(outputFormat.get()), nullptr) << "Expected JPEGFormat.";
    } else if (options.outputFormat == "png") {
        ASSERT_NE(dynamic_cast<PNGFormat*>(outputFormat.get()), nullptr) << "Expected PNGFormat.";
    }

    // Verify output file path extension
    std::string expectedExtension = options.outputFormat;
    std::string actualExtension = getFileExtension(options.outputPath);
    EXPECT_EQ(actualExtension, expectedExtension) << "Output file extension does not match desired output format.";

    // Clean up
    std::remove(PATH);
}

// InvalidFormat
TEST(CLIArgumentTest, InvalidFormat) {
    int argc = 4;
    char* argv[] = {
        (char*)"file_converter",
        (char*)PATH,
        (char*)"-t",
        (char*)"bmp"
    };

    // Create a temporary input file
    std::ofstream outfile(PATH);
    outfile.close();

    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
    EXPECT_EQ(options.errorMessage, "Error: Unsupported output format 'bmp'.");

    // Clean up
    std::remove(PATH);
}

// MissingOutputPath
TEST(CLIArgumentTest, MissingOutputPath) {
    int argc = 4;
    char* argv[] = {
        (char*)"file_converter",
        (char*)PATH,
        (char*)"-t",
        (char*)"jpeg"
    };

    // Create a temporary input file
    std::ofstream outfile(PATH);
    outfile.close();

    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
    EXPECT_EQ(options.errorMessage, "Error: No output path specified.");

    // Clean up
    std::remove(PATH);
}

// UnknownOption
TEST(CLIArgumentTest, UnknownOption) {
    int argc = 5;
    char* argv[] = {
        (char*)"file_converter",
        (char*)PATH,
        (char*)"-x",
        (char*)"jpeg",
        (char*)"-p",
        (char*)"output.jpeg"
    };

    // Create a temporary input file
    std::ofstream outfile(PATH);
    outfile.close();

    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
    EXPECT_EQ(options.errorMessage, "Error: Unknown option '-x'.");

    // Clean up
    std::remove(PATH);
}

// DuplicateOption
TEST(CLIArgumentTest, DuplicateOption) {
    int argc = 8;
    char* argv[] = {
        (char*)"file_converter",
        (char*)PATH,
        (char*)"-t",
        (char*)"jpeg",
        (char*)"-t",
        (char*)"png",
        (char*)"-p",
        (char*)"output.jpeg"
    };

    // Create a temporary input file
    std::ofstream outfile(PATH);
    outfile.close();

    CLIOptions options = parseArguments(argc, argv);
    EXPECT_TRUE(options.showHelp);
    EXPECT_EQ(options.errorMessage, "Error: Duplicate output format specified.");

    // Clean up
    std::remove(PATH);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}