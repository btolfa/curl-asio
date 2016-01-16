cmake_minimum_required (VERSION 2.8)

project(curl-asio)

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

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
