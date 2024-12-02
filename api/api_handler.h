#ifndef API_HANDLER_H
#define API_HANDLER_H

#include "converter.h"
#include "fileformat.h"
#include "utils.h"
#include <converter.h>
#include <crow.h>
#include <filesystem> // For creating/checking directories
#include <fstream>    // For file handling

class APIHandler {
public:
  void startServer(int port);
};

#endif
