cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
project(examples CXX)

find_package(Threads REQUIRED)

add_executable(asynchronous asynchronous.cpp)
target_link_libraries(asynchronous Threads::Threads curl-asio)

add_executable(synchronous synchronous.cpp)
target_link_libraries(synchronous Threads::Threads curl-asio)
