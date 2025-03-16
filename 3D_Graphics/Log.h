#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>

class Log {
public:
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

    ~Log();

private:
    static std::ofstream logFile;  // Static member to store the log file stream
};

#endif // LOG_H
