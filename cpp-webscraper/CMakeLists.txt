cmake_minimum_required(VERSION 3.08)

project(Cpp-webscraper)

find_package(fmt CONFIG REQUIRED)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

add_executable(Cpp-webscraper main.cpp cpp-webscraper.cpp  "cpp-webscraper.h")

target_link_libraries(Cpp-webscraper PRIVATE fmt::fmt ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})