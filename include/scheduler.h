#pragma once

#include <iostream>
#include <string>
#include <fstream>

#if defined(__WIN32) || defined(_WIN64)
#include <windows.h>
#include <winternl.h>
#include <mstask.h>
#endif

#if defined(__linux__)
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#if defined(__APPLE__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach-o/dyld.h>
#endif

class Scheduler
{
public:
    void start(bool schedule);

    bool scheduleLoggerOnWindows();
    bool scheduleLoggerOnLinux();
    bool scheduleLoggerOnMacOs();
};