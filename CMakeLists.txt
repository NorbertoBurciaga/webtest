cmake_minimum_required (VERSION 2.6)

project (webtest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(webtest webtest.cpp)
target_link_libraries(webtest pthread fmt http_parser)