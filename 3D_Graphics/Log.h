// Log.h
#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>

class Log {
public:
    static void info(const std::string& message);
    static void error(const std::string& message);
    static void warn(const std::string& message);
};

#endif
