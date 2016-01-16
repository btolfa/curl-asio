# Locate ASIO-headers (http://think-async.com/Asio)

FIND_PATH(ASIO_INCLUDE_DIR
    NAMES
        asio.hpp
    HINTS
        ${ASIO_ROOT}
    PATHS
        /usr/include
        /usr/local/include
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ASIO DEFAULT_MSG ASIO_INCLUDE_DIR)
if (ASIO_FOUND)
    mark_as_advanced(ASIO_INCLUDE_DIR)

    add_library(asio::asio INTERFACE IMPORTED)
    set_property(TARGET asio::asio PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${ASIO_INCLUDE_DIR}")
    set_property(TARGET asio::asio PROPERTY INTERFACE_COMPILE_FEATURES cxx_generic_lambdas)
    set_property(TARGET asio::asio PROPERTY INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE)
endif()