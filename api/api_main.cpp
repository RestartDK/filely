#include "api_handler.h"

int main() {
  crow::SimpleApp app; // define your crow application

  APIHandler apiHandler;

  apiHandler.startServer(18080);
}
