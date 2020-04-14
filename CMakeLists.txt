cmake_minimum_required(VERSION 3.1)
project(xlxd)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(XLXD_VERSION "1.4.0")

include(cmake/config/packaging.cmake)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
message("Threads flags: ${CMAKE_THREAD_LIBS_INIT}")

add_subdirectory(3rdparty)
#add_subdirectory(src)
add_subdirectory(ambed)
add_subdirectory(ambedtest)

message("${CPACK_COMPONENTS_ALL}")
