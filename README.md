## loggy
loggy is a simple educational keylogger for windows, macos and linux. It is written in C++ and records keystrokes in a text file. It is not meant to be used for malicious purposes. It is meant to be used for educational purposes only. It is a simple keylogger and does not have any advanced features.

## Usage
To use loggy, follow these steps:

1. Clone the repository
```bash	
git clone https://github.com/mendax0110/loggy.git
```
2. Navigate to the loggy directory
```bash
cd loggy
```
3. Create a build directory
```bash
mkdir build
```
4. Navigate to the build directory
```bash
cd build
```
5. Generat the build files
```bash
cmake ..
```
6. Build the project
```bash
cmake --build .
```
7. Run the executable
```bash
./loggy
```
8. Run the executable as a scheduled task
```bash
./loggy -sd
```

## Supported Platforms
loggy is supported on the following platforms:
- Windows
- MacOS
- Linux