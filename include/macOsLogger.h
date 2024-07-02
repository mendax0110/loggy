#pragma once

#if defined(__APPLE__)
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <map>
#include <stdexcept>
#include <sys/stat.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

class MacOsLogger
{
public:
    MacOsLogger();
    ~MacOsLogger();

    void startLogging();

private:
    std::string logFileName;
    std::ofstream logFile;
    std::map<UInt32, std::string> keyMap;

    static OSStatus eventHandler(EventHandlerCallRef nextHandler, EventRef event, void* userData);
    void initializeKeyMap();
};
#endif
