// Log.cpp
#include "Log.h"

void Log::info(const std::string& message) {
    std::cout << "[INFO]: " << message << std::endl;
}

void Log::error(const std::string& message) {
    std::cerr << "[ERROR]: " << message << std::endl;
}

void Log::warn(const std::string& message) {
    std::cout << "[WARNING]: " << message << std::endl;
}
