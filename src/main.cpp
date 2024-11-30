#include "headers/start_server.h"

int main() {
  if (std::filesystem::exists(SHARED_DIR)) {
    std::filesystem::create_directory(SHARED_DIR);
  }

  start_server();
  return 0;
}