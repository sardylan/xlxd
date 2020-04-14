set(CPACK_COMPONENTS_GROUPING IGNORE)

set(CPACK_PACKAGE_NAME "xlxd")
set(CPACK_PACKAGE_VENDOR "LX3JL")
set(CPACK_PACKAGE_VERSION "${XLXD_VERSION}")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Luca Cireddu IS0GVH")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "XLX Reflector")
set(CPACK_GENERATOR "DEB")

execute_process(COMMAND dpkg --print-architecture
        OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)

set(CPACK_DEB_COMPONENT_INSTALL ON)

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

include(CPack)
