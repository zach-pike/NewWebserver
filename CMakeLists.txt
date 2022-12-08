cmake_minimum_required(VERSION 3.25.0)

project(WebServer)

file(GLOB_RECURSE SRC src/*.cpp)

include_directories(src/webserver/interfaces)
include_directories(src/webserver/classes)

add_executable(main ${SRC})