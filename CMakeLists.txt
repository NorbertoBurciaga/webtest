cmake_minimum_required (VERSION 2.6)

project (webtest)

add_executable(webtest webtest.cpp)
target_link_libraries(webtest pthread fmt http_parser)