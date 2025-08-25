cmake_minimum_required (VERSION 3.8)
project("GenEnum" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE GEN_ENUM_HEADER_FILES ${SOURCES_DIR}/*.hpp)
add_library(${PROJECT_NAME} INTERFACE ${GEN_ENUM_HEADER_FILES})
add_library(GenEnum::GenEnum ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${SOURCES_DIR})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/preprocessor)
target_link_libraries(${PROJECT_NAME} INTERFACE Boost::preprocessor)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party/preprocessor/include)
