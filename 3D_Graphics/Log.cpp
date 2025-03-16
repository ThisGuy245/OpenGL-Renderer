#include "Log.h"

// Initialize the static log file stream
std::ofstream Log::logFile("log.txt", std::ios::out | std::ios::app);  // Open file for appending

void Log::info(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[INFO]: " << message << std::endl;  // Log to file
    }
    else {
        std::cout << "[INFO]: " << message << std::endl;  // Fallback to console if file isn't open
    }
}

void Log::warn(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[WARNING]: " << message << std::endl;  // Log to file
    }
    else {
        std::cout << "[WARNING]: " << message << std::endl;  // Fallback to console
    }
}

void Log::error(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[ERROR]: " << message << std::endl;  // Log to file
    }
    else {
        std::cerr << "[ERROR]: " << message << std::endl;  // Fallback to console
    }
}

Log::~Log() {
    if (logFile.is_open()) {
        logFile.close();  // Close the log file when the program ends
    }
}
