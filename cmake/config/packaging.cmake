execute_process(COMMAND dpkg --print-architecture
        OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CPACK_COMPONENTS_GROUPING IGNORE)

set(CPACK_PACKAGE_NAME "xlx")
set(CPACK_PACKAGE_VENDOR "LX3JL")
set(CPACK_PACKAGE_DESCRIPTION "XLX Reflector")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "XLX Reflector binaries, with AMBE transcoder utility")
set(CPACK_PACKAGE_VERSION_MAJOR "${XLX_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${XLX_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${XLX_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${XLX_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Luca Cireddu IS0GVH")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)

set(CPACK_DEB_COMPONENT_INSTALL ON)

SET(CPACK_COMPONENTS_ALL
        ambed
        xlxd)

include(CPack)

cpack_add_component(ambed
        DISPLAY_NAME "AMBEd Transcoding daemon"
        DESCRIPTION "AMBEd is a daemon for transcoding between AMBE-Plus and AMBE2-Plus"
        REQUIRED)

cpack_add_component(xlxd
        DISPLAY_NAME "XLX Reflector"
        DESCRIPTION "XLX Reflector for D-Star"
        REQUIRED)