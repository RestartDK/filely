#include "converter.h"
#include "jpegformat.h"
#include "jpgformat.h"
#include "pngformat.h"
#include "bmpformat.h"
#include "textformat.h"
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
using namespace std;

void Converter::convert() {
    // Determine if the input and output formats handle binary data
    bool inputIsBinary = false;
    bool outputIsBinary = false;

    // Check if input format is binary (images)
    if (dynamic_cast<PNGFormat *>(inputFormat) != nullptr ||
        dynamic_cast<JPGFormat *>(inputFormat) != nullptr ||
        dynamic_cast<JPEGFormat *>(inputFormat) != nullptr ||
        dynamic_cast<BMPFormat *>(inputFormat) != nullptr) { // Added BMPFormat
        inputIsBinary = true;
    }

    // Check if output format is binary (images)
    if (dynamic_cast<PNGFormat *>(outputFormat) != nullptr ||
        dynamic_cast<JPGFormat *>(outputFormat) != nullptr ||
        dynamic_cast<JPEGFormat *>(outputFormat) != nullptr ||
        dynamic_cast<BMPFormat *>(outputFormat) != nullptr) { // Added BMPFormat
        outputIsBinary = true;
    }

    // Open input file with appropriate mode
    ifstream inputFile;
    if (inputIsBinary) {
        inputFile.open(inputFilePath, ios::binary);
    } else {
        inputFile.open(inputFilePath);
    }

    if (!inputFile.is_open()) {
        throw runtime_error("Failed to open input file: " + inputFilePath);
    }

    // Parse the input file
    cout << "Parsing input file: " << inputFilePath << endl;

    if (inputIsBinary) {
        // Parse binary data
        vector<uchar> data = inputFormat->parseBinary(inputFile);
        inputFile.close();

        if (data.empty()) {
            throw runtime_error("Failed to parse binary input file.");
        }

        // Print the parsed data size for debugging
        cout << "Parsed binary data size: " << data.size() << " bytes" << endl;

        if (outputIsBinary) {
            // Format binary data to binary output
            cout << "Formatting binary data to binary output file: " << outputFilePath << endl;
            string result = outputFormat->formatBinary(data, outputFilePath);
            cout << result << endl;
        } else {
            // Conversion from binary to text
            cout << "Formatting binary data to text output file: " << outputFilePath << endl;

            // Decode the image data
            cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
            if (image.empty()) {
                cerr << "Error: Failed to decode image data." << endl;
                throw runtime_error("Failed to decode image data.");
            }

            // Convert image data to text representation
            ostringstream oss;
            // Write image dimensions and channels
            oss << image.rows << " " << image.cols << " " << image.channels() << "\n";

            // Write pixel data
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    if (image.channels() == 1) {
                        uchar pixel = image.at<uchar>(i, j);
                        oss << static_cast<int>(pixel) << " ";
                    } else {
                        cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
                        oss << static_cast<int>(pixel[2]) << " "  // R
                            << static_cast<int>(pixel[1]) << " "  // G
                            << static_cast<int>(pixel[0]) << " "; // B
                    }
                }
                oss << "\n";
            }

            // Get the text data
            string textData = oss.str();

            // Use output format's formatText method
            string result = outputFormat->formatText(textData, outputFilePath);
            cout << result << endl;
        }
    } else {
        // Parse text data
        string data = inputFormat->parseText(inputFile);
        inputFile.close();

        if (data.empty()) {
            throw runtime_error("Failed to parse text input file.");
        }

        // Print the parsed data size for debugging
        cout << "Parsed text data size: " << data.size() << " characters" << endl;

        if (outputIsBinary) {
            // Conversion from text to binary
            cout << "Formatting text data to binary output file: " << outputFilePath << endl;

            // Reconstruct image from text data
            istringstream iss(data);
            int rows, cols, channels;
            if (!(iss >> rows >> cols >> channels)) {
                cerr << "Error: Invalid image dimensions in text data." << endl;
                throw runtime_error("Invalid image dimensions in text data.");
            }

            cv::Mat image;
            if (channels == 1) {
                image = cv::Mat(rows, cols, CV_8UC1);
            } else {
                image = cv::Mat(rows, cols, CV_8UC3);
            }

            // Read pixel data
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (channels == 1) {
                        int pixelValue;
                        if (!(iss >> pixelValue)) {
                            cerr << "Error: Not enough pixel data in text." << endl;
                            throw runtime_error("Not enough pixel data in text.");
                        }
                        image.at<uchar>(i, j) = static_cast<uchar>(pixelValue);
                    } else {
                        int r, g, b;
                        if (!(iss >> r >> g >> b)) {
                            cerr << "Error: Not enough pixel data in text." << endl;
                            throw runtime_error("Not enough pixel data in text.");
                        }
                        image.at<cv::Vec3b>(i, j) = cv::Vec3b(static_cast<uchar>(b),
                                                              static_cast<uchar>(g),
                                                              static_cast<uchar>(r));
                    }
                }
            }

            // Encode the image to binary data
            vector<uchar> encodedData;
            if (!cv::imencode(".bmp", image, encodedData)) {
                cerr << "Error: Failed to encode image to BMP format." << endl;
                throw runtime_error("Failed to encode image to BMP format.");
            }

            // Use output format's formatBinary method
            string result = outputFormat->formatBinary(encodedData, outputFilePath);
            cout << result << endl;
        } else {
            // Format text data to text output
            cout << "Formatting text data to text output file: " << outputFilePath << endl;
            string result = outputFormat->formatText(data, outputFilePath);
            cout << result << endl;
        }
    }
}
