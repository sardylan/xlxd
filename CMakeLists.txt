cmake_minimum_required(VERSION 3.1)
project(XLX)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(XLX_VERSION_MAJOR "1")
set(XLX_VERSION_MINOR "4")
set(XLX_VERSION_PATCH "0")

set(XLX_VERSION "${XLX_VERSION_MAJOR}.${XLX_VERSION_MINOR}.${XLX_VERSION_PATCH}")

include(cmake/config/packaging.cmake)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
message("Threads flags: ${CMAKE_THREAD_LIBS_INIT}")

add_subdirectory(src)
add_subdirectory(ambed)
add_subdirectory(ambedtest)
