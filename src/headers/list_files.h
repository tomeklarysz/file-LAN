#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
const std::string SHARED_DIR = "./shared_files";
std::string list_files();