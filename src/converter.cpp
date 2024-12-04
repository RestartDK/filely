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
    try {
        // Determine if the input and output formats handle binary data
        bool inputIsBinary = false;
        bool outputIsBinary = false;

        // Check if input format is binary (images)
        if (dynamic_cast<PNGFormat *>(inputFormat) != nullptr ||
            dynamic_cast<JPGFormat *>(inputFormat) != nullptr ||
            dynamic_cast<JPEGFormat *>(inputFormat) != nullptr ||
            dynamic_cast<BMPFormat *>(inputFormat) != nullptr) {
            inputIsBinary = true;
        }

        // Check if output format is binary (images)
        if (dynamic_cast<PNGFormat *>(outputFormat) != nullptr ||
            dynamic_cast<JPGFormat *>(outputFormat) != nullptr ||
            dynamic_cast<JPEGFormat *>(outputFormat) != nullptr ||
            dynamic_cast<BMPFormat *>(outputFormat) != nullptr) {
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
            throw runtime_error("Error: Unable to open input file: " + inputFilePath);
        }

        cout << "Parsing input file: " << inputFilePath << endl;

        if (inputIsBinary) {
            // Parse binary data
            vector<uchar> data;
            try {
                data = inputFormat->parseBinary(inputFile);
            } catch (const BinaryParsingException &e) {
                throw runtime_error("Error while parsing binary input file: " + string(e.what()));
            }
            inputFile.close();

            if (data.empty()) {
                throw runtime_error("Error: Parsed binary input file is empty.");
            }

            cout << "Parsed binary data size: " << data.size() << " bytes" << endl;

            if (outputIsBinary) {
                // Format binary data to binary output
                cout << "Formatting binary data to binary output file: " << outputFilePath << endl;
                try {
                    string result = outputFormat->formatBinary(data, outputFilePath);
                    cout << result << endl;
                } catch (const BinaryFormattingException &e) {
                    throw runtime_error("Error while formatting binary data: " + string(e.what()));
                }
            } else {
                // Conversion from binary to text
                cout << "Formatting binary data to text output file: " << outputFilePath << endl;
                cv::Mat image = cv::imdecode(data, cv::IMREAD_UNCHANGED);
                if (image.empty()) {
                    throw runtime_error("Error: Failed to decode image data.");
                }

                ostringstream oss;
                oss << image.rows << " " << image.cols << " " << image.channels() << "\n";

                for (int i = 0; i < image.rows; ++i) {
                    for (int j = 0; j < image.cols; ++j) {
                        if (image.channels() == 1) {
                            oss << static_cast<int>(image.at<uchar>(i, j)) << " ";
                        } else {
                            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
                            oss << static_cast<int>(pixel[2]) << " "  // R
                                << static_cast<int>(pixel[1]) << " "  // G
                                << static_cast<int>(pixel[0]) << " "; // B
                        }
                    }
                    oss << "\n";
                }

                string textData = oss.str();
                try {
                    string result = outputFormat->formatText(textData, outputFilePath);
                    cout << result << endl;
                } catch (const TextFormattingException &e) {
                    throw runtime_error("Error while formatting text data: " + string(e.what()));
                }
            }
        } else {
            // Parse text data
            string data;
            try {
                data = inputFormat->parseText(inputFile);
            } catch (const TextParsingException &e) {
                throw runtime_error("Error while parsing text input file: " + string(e.what()));
            }
            inputFile.close();

            if (data.empty()) {
                throw runtime_error("Error: Parsed text input file is empty.");
            }

            cout << "Parsed text data size: " << data.size() << " characters" << endl;

            if (outputIsBinary) {
                // Conversion from text to binary
                cout << "Formatting text data to binary output file: " << outputFilePath << endl;

                istringstream iss(data);
                int rows, cols, channels;
                if (!(iss >> rows >> cols >> channels)) {
                    throw runtime_error("Error: Invalid image dimensions in text data.");
                }

                cv::Mat image;
                if (channels == 1) {
                    image = cv::Mat(rows, cols, CV_8UC1);
                } else {
                    image = cv::Mat(rows, cols, CV_8UC3);
                }

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (channels == 1) {
                            int pixelValue;
                            if (!(iss >> pixelValue)) {
                                throw runtime_error("Error: Insufficient pixel data in text.");
                            }
                            image.at<uchar>(i, j) = static_cast<uchar>(pixelValue);
                        } else {
                            int r, g, b;
                            if (!(iss >> r >> g >> b)) {
                                throw runtime_error("Error: Insufficient pixel data in text.");
                            }
                            image.at<cv::Vec3b>(i, j) = cv::Vec3b(static_cast<uchar>(b),
                                                                  static_cast<uchar>(g),
                                                                  static_cast<uchar>(r));
                        }
                    }
                }

                vector<uchar> encodedData;
                if (!cv::imencode(".bmp", image, encodedData)) {
                    throw runtime_error("Error: Failed to encode image to BMP format.");
                }

                try {
                    string result = outputFormat->formatBinary(encodedData, outputFilePath);
                    cout << result << endl;
                } catch (const BinaryFormattingException &e) {
                    throw runtime_error("Error while formatting binary data: " + string(e.what()));
                }
            } else {
                // Format text data to text output
                cout << "Formatting text data to text output file: " << outputFilePath << endl;
                try {
                    string result = outputFormat->formatText(data, outputFilePath);
                    cout << result << endl;
                } catch (const TextFormattingException &e) {
                    throw runtime_error("Error while formatting text data: " + string(e.what()));
                }
            }
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    } catch (...) {
        cerr << "An unexpected error occurred during conversion." << endl;
    }
}