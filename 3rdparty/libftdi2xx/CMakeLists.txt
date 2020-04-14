set(FTDI2XX_OS "Linux") # TODO: support multiple architectures and OSs
set(FTDI2XX_VERSION "1.4.8")

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(FTDI2XX_ARCH "x86_64")
    set(FTDI2XX_SHA256 "815d880c5ec40904f062373e52de07b2acaa428e54fece98b31e6573f5d261a0")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "i?86")
    set(FTDI2XX_URL "i386")
    set(FTDI2XX_SHA256 "84c9aaf7288a154faf0e2814ba590ec965141c698b2a00bffc94d8e0c7ebeb4c")
endif ()

set(FTDI2XX_URL "https://www.ftdichip.com/Drivers/D2XX/${FTDI2XX_OS}/libftd2xx-${FTDI2XX_ARCH}-${FTDI2XX_VERSION}.gz")
set(FTDI2XX_FILENAME "libftd2xx-${FTDI2XX_ARCH}-${FTDI2XX_VERSION}.tar.gz")
set(FTDI2XX_FILEPATH "./3rdparty/libftdi2xx/${FTDI2XX_FILENAME}")

if (NOT EXISTS ${FTDI2XX_FILEPATH})
    message(STATUS "Downloading libftdi2xxx: ${FTDI2XX_URL}")
    file(DOWNLOAD "${FTDI2XX_URL}" "${FTDI2XX_FILEPATH}"
            EXPECTED_HASH "SHA256=${FTDI2XX_SHA256}"
            SHOW_PROGRESS)
endif ()

message(STATUS "Extracting ${FTDI2XX_FILENAME}")
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf "${FTDI2XX_FILENAME}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/release/build/libftd2xx.so.1.4.8"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT libftd2xx)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/release/build/libftd2xx.a"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT libftd2xx)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/release/ftd2xx.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT libftd2xx)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/release/WinTypes.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT libftd2xx)

cpack_add_component(libftd2xx
        DISPLAY_NAME "FTDI2XX Library"
        DESCRIPTION "D2XX drivers allow direct access to the USB device through a DLL."
        REQUIRED)
