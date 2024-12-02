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
          // Get the file type to convert to from query params
          if (!fileType) {
            return crow::response(400,
                                  "Must provide a file type to convert to");
          }

          // Save the file to the `data` folder
          std::string inputPath = "./data/" + fileName;
          std::string outputPath =
              "./data/" + fileNameWithoutExtension + "." + fileType;
          std::ofstream outFile(inputPath, std::ios::binary);
          outFile.write(filePart.body.data(), filePart.body.size());
          outFile.close();

          // Conversion logic
          std::unique_ptr<FileFormat> inputFormat(getFileFormat(inputPath));
          std::unique_ptr<FileFormat> outputFormat(
              getFormatFromString(fileType));

          Converter converter(inputPath, outputPath, inputFormat.get(),
                              outputFormat.get());

          converter.convert();

          return crow::response(200, "File saved to data folder");
        } catch (const std::exception &e) {
          std::cerr << "Exception occurred: " << e.what() << std::endl;
          return crow::response(500, "Unexpected error occurred: ");
        }
      });

  // Endpoint to download files
  CROW_ROUTE(app, "/download")
      .methods(crow::HTTPMethod::GET)([](const crow::request &req) {
        try {
          // Extract the filename from query parameters
          char *fileName = req.url_params.get("file");
          if (!fileName) {
            return crow::response(400, "Missing 'file' query parameter.");
          }

          // Build the file path
          std::string filePath = "./data/" + std::string(fileName);

          // Check if the file exists
          if (!std::filesystem::exists(filePath)) {
            return crow::response(404, "File not found: " + filePath);
          }

          // Read the file content
          std::ifstream inFile(filePath, std::ios::binary);
          std::ostringstream fileContent;
          fileContent << inFile.rdbuf();
          inFile.close();

          // Serve the file as a downloadable response
          crow::response res(fileContent.str());
          res.add_header("Content-Disposition",
                         "attachment; filename=" + std::string(fileName));
          res.add_header("Content-Type", "application/octet-stream");
          return res;
        } catch (const std::exception &e) {
          return crow::response(500, "Unexpected error occurred: " +
                                         std::string(e.what()));
        }
      });

  app.port(port).multithreaded().run();
}
