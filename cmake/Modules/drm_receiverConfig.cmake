INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DRM_RECEIVER drm_receiver)

FIND_PATH(
    DRM_RECEIVER_INCLUDE_DIRS
    NAMES drm_receiver/api.h
    HINTS $ENV{DRM_RECEIVER_DIR}/include
        ${PC_DRM_RECEIVER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DRM_RECEIVER_LIBRARIES
    NAMES gnuradio-drm_receiver
    HINTS $ENV{DRM_RECEIVER_DIR}/lib
        ${PC_DRM_RECEIVER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DRM_RECEIVER DEFAULT_MSG DRM_RECEIVER_LIBRARIES DRM_RECEIVER_INCLUDE_DIRS)
MARK_AS_ADVANCED(DRM_RECEIVER_LIBRARIES DRM_RECEIVER_INCLUDE_DIRS)

