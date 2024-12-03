#include "api_handler.h"
#include "converter.h"
#include "fileformat.h"
#include "utils.h"
#include <filesystem>
#include <fstream>

void APIHandler::startServer(int port) {
  crow::SimpleApp app;

  // Ensure the `data` folder exists in the project's root directory
  std::filesystem::create_directory("./data");

  // Endpoint to check server status
  CROW_ROUTE(app, "/status")([]() { return "Filely API is running"; });

  // Endpoint to convert files
  CROW_ROUTE(app, "/convert")
      .methods(crow::HTTPMethod::POST)([](const crow::request &req) {
        try {
          // Parse multipart message from request
          crow::multipart::message msg(req);

          // Extract file part by name
          auto filePart = msg.get_part_by_name("file");
          if (filePart.body.empty()) {
            return crow::response(400, "No file part found or file is empty.");
          }

          // Retrieve the filename from the headers
          auto contentDisposition =
              filePart.get_header_object("Content-Disposition");
          std::string fileName = contentDisposition.params["filename"];
          if (fileName.empty()) {
            fileName = "uploaded_file"; // Fallback to a default name
          }

          // Get the filename without the extension (.jpeg, .png, etc)
          std::filesystem::path filePath(fileName);
          std::string fileNameWithoutExtension = filePath.stem().string();

          char *fileType = req.url_params.get("type");
          if (!fileType) {
            return crow::response(400,
                                  "Must provide a file type to convert to");
          }

          // Create temporary paths for processing
          std::string tempInputPath = "./data/temp_" + fileName;
          std::string tempOutputPath = "./data/temp_" +
                                       fileNameWithoutExtension + "." +
                                       std::string(fileType);

          // Save the input file temporarily
          std::ofstream outFile(tempInputPath, std::ios::binary);
          outFile.write(filePart.body.data(), filePart.body.size());
          outFile.close();

          // Conversion logic
          std::unique_ptr<FileFormat> inputFormat(getFileFormat(tempInputPath));
          std::unique_ptr<FileFormat> outputFormat(
              getFormatFromString(fileType));

          Converter converter(tempInputPath, tempOutputPath, inputFormat.get(),
                              outputFormat.get());
          converter.convert();

          // Read the converted file
          std::ifstream convertedFile(tempOutputPath, std::ios::binary);
          std::ostringstream convertedContent;
          convertedContent << convertedFile.rdbuf();
          convertedFile.close();

          // Clean up temporary files
          std::filesystem::remove(tempInputPath);
          std::filesystem::remove(tempOutputPath);

          // Return the converted file directly
          crow::response res(convertedContent.str());
          res.add_header("Content-Disposition",
                         "attachment; filename=" + fileNameWithoutExtension +
                             "." + std::string(fileType));
          res.add_header("Content-Type", "application/octet-stream");
          return res;

        } catch (const std::exception &e) {
          std::cerr << "Exception occurred: " << e.what() << std::endl;
          return crow::response(500, "Unexpected error occurred: " +
                                         std::string(e.what()));
        }
      });

  app.port(port).multithreaded().run();
}
