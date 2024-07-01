#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <any>
#include <iostream>
#include <random>

class Obfuscator
{
public:
    std::string obfuscateString(const std::string& input);
    std::string deobfuscateString(const std::string& input);

    template<typename T>
    void rename(T& symbol);

    template<typename ReturnType>
    void registerMethod(const std::string& obfuscatedName, std::function<ReturnType()> method);

    template<typename ReturnType>
    ReturnType callMethod(const std::string& obfuscatedName);

    void registerMethod(const std::string& obfuscatedName, std::function<void()> method);
    void callMethod(const std::string& obfuscatedName);

private:
    std::unordered_map<std::string, std::function<std::any()>> methodMap;
    std::unordered_map<std::string, std::function<void()>> voidMethodMap;
};

inline std::string Obfuscator::obfuscateString(const std::string& input)
{
    std::string obfuscatedString;
    for (const auto& character : input)
    {
        obfuscatedString += character ^ 0x1F;
    }
    return obfuscatedString;
}

inline std::string Obfuscator::deobfuscateString(const std::string& input)
{
    std::string deobfuscatedString;
    for (const auto& character : input)
    {
        deobfuscatedString += character ^ 0x1F;
    }
    return deobfuscatedString;
}

template<typename T>
void Obfuscator::rename(T& symbol)
{
    static std::random_device randomDevice;
    static std::mt19937 randomEngine(randomDevice());
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 2);

    for (char& c : symbol)
    {
        c = charset[distribution(randomEngine)];
    }
}

template<typename ReturnType>
void Obfuscator::registerMethod(const std::string& obfuscatedName, std::function<ReturnType()> method)
{
    methodMap[obfuscatedName] = [method]() -> std::any
    {
        return std::any(method());
    };
}

template<typename ReturnType>
ReturnType Obfuscator::callMethod(const std::string& obfuscatedName)
{
    if (methodMap.count(obfuscatedName) > 0)
    {
        std::any result = methodMap[obfuscatedName]();
        try
        {
            return std::any_cast<ReturnType>(result);
        }
        catch (const std::bad_any_cast& e)
        {
            std::cerr << "Error: Bad cast when calling method '" << obfuscatedName << "': " << e.what() << std::endl;
            throw;
        }
    }
    else
    {
        std::cerr << "Error: Method '" << obfuscatedName << "' not found." << std::endl;
        throw std::runtime_error("Method not found");
    }
}

inline void Obfuscator::registerMethod(const std::string& obfuscatedName, std::function<void()> method)
{
    voidMethodMap[obfuscatedName] = method;
}

inline void Obfuscator::callMethod(const std::string& obfuscatedName)
{
    if (voidMethodMap.count(obfuscatedName) > 0)
    {
        voidMethodMap[obfuscatedName]();
    }
    else
    {
        std::cerr << "Error: Method '" << obfuscatedName << "' not found." << std::endl;
        throw std::runtime_error("Method not found");
    }
}
