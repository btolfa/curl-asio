# Find curl-asio
# Oliver Kuckertz <oliver.kuckertz@mologie.de>, 2013-10-06, public domain
#
# Searches for:
# <prefix>/include/curl-asio.h
# curlasio.lib or libcurlasio.lib
# curlasiod.lib or libcurlasiod.lib
#
# Defines:
# CURLASIO_INCLUDE_DIR
# CURLASIO_LIBRARIES
#
# Uses:
# CURLASIO_ROOT
# CURLASIO_STATIC
#

FIND_PATH(CURLASIO_INCLUDE_DIR NAMES curl-asio.h HINTS ${CURLASIO_ROOT} PATH_SUFFIXES include)
MARK_AS_ADVANCED(CURLASIO_INCLUDE_DIR)

OPTION(CURLASIO_STATIC "Use the static curl-asio library." ON)
MARK_AS_ADVANCED(CURLASIO_STATIC)

IF(CURLASIO_STATIC)
	SET(CURLASIO_LIBRARY_NAME curlasio)
ELSE()
	SET(CURLASIO_LIBRARY_NAME libcurlasio)
ENDIF()

FIND_LIBRARY(CURLASIO_LIBRARY_DEBUG "${CURLASIO_LIBRARY_NAME}d" HINTS ${CURLASIO_ROOT} PATH_SUFFIXES lib)
FIND_LIBRARY(CURLASIO_LIBRARY_RELEASE "${CURLASIO_LIBRARY_NAME}" HINTS ${CURLASIO_ROOT} PATH_SUFFIXES lib)
MARK_AS_ADVANCED(CURLASIO_LIBRARY_DEBUG CURLASIO_LIBRARY_RELEASE)

IF(CURLASIO_LIBRARY_DEBUG AND NOT CURLASIO_LIBRARY_RELEASE)
	SET(CURLASIO_LIBRARIES ${CURLASIO_LIBRARY_DEBUG})
ELSEIF(NOT CURLASIO_LIBRARY_DEBUG AND CURLASIO_LIBRARY_RELEASE)
	SET(CURLASIO_LIBRARIES ${CURLASIO_LIBRARY_RELEASE})
ELSE()
	SET(CURLASIO_LIBRARIES)
	IF(CURLASIO_LIBRARY_DEBUG)
		LIST(APPEND CURLASIO_LIBRARIES debug ${CURLASIO_LIBRARY_DEBUG})
		SET(CURLASIO_LIBRARY_DEBUG_FOUND TRUE)
	ENDIF()
	IF(CURLASIO_LIBRARY_RELEASE)
		LIST(APPEND CURLASIO_LIBRARIES optimized ${CURLASIO_LIBRARY_RELEASE})
		SET(CURLASIO_LIBRARY_RELEASE_FOUND TRUE)
	ENDIF()
ENDIF()

FIND_PACKAGE(CURLASIO-CURL REQUIRED)
SET(CURLASIO_INCLUDE_DIRS ${CURLASIO_INCLUDE_DIR} ${CURL_INCLUDE_DIR})

IF(CURLASIO_STATIC)
	LIST(APPEND CURLASIO_LIBRARIES ${CURL_LIBRARIES})
ENDIF()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(CURLASIO
	REQUIRED_VARS
		CURLASIO_INCLUDE_DIR
		CURLASIO_LIBRARIES
	FAIL_MESSAGE
		"Could not find curl-asio, ensure it is in either the system's or CMake's path, or set CURLASIO_ROOT."
	)
