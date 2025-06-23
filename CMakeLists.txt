cmake_minimum_required (VERSION 3.8)
project ("GenEnum" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE GEN_ENUM_HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp)
add_library (${PROJECT_NAME} INTERFACE ${GEN_ENUM_HEADER_FILES})

add_subdirectory (${CMAKE_CURRENT_LIST_DIR}/third_party/preprocessor)
target_link_libraries (${PROJECT_NAME} INTERFACE Boost::preprocessor)
include_directories (${CMAKE_CURRENT_LIST_DIR}/third_party/preprocessor/include)

if(DEFINED GENENUM_USE_PREFIX_K)
    target_compile_definitions(${PROJECT_NAME} INTERFACE GENENUM_USE_PREFIX_K)
endif()
