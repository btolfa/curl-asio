# Locate ASIO-headers (http://think-async.com/Asio)

FIND_PATH(ASIO_INCLUDE_DIR
  NAMES
    asio.hpp
  PATHS
    /usr/include
    /usr/local/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ASIO DEFAULT_MSG ASIO_INCLUDE_DIR)
mark_as_advanced(ASIO_INCLUDE_DIR)