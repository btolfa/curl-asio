cmake_minimum_required (VERSION 3.0 FATAL_ERROR)

project(curl-asio CXX)

# Append the path to the custom cmake modules from this project to the CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


find_package(Boost)
find_package(Asio REQUIRED)
find_package(CURLASIO-CURL REQUIRED)

set(HEADERS
    include/curl-asio/config.h
    include/curl-asio/easy.h
    include/curl-asio/error_code.h
    include/curl-asio/form.h
    include/curl-asio/initialization.h
    include/curl-asio/multi.h
    include/curl-asio/native.h
    include/curl-asio/share.h
    include/curl-asio/socket_info.h
    include/curl-asio/string_list.h
    include/curl-asio.h
)

set(SOURCES
    src/easy.cpp
    src/error_code.cpp
    src/form.cpp
    src/initialization.cpp
    src/multi.cpp
    src/share.cpp
    src/string_list.cpp
    ${HEADERS}
)

include_directories(include
        ${ASIO_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR})

add_library(curl-asio STATIC ${SOURCES})
target_link_libraries(curl-asio
        ${CURL_LIBRARIES}
        asio::asio
        )

set_property(TARGET curl-asio PROPERTY CXX_STANDARD 14)