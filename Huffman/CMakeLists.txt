cmake_minimum_required(VERSION 3.3)
project(Huffman)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/Huffman.h
        src/huffman/Huffman.cpp
        include/TreeNode.h
        src/huffman/TreeNode.cpp
        )
set(HUFFMAN_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Huffman/include)

#file(GLOB HUFFMAN_SRC ${SOURCE_FILES})


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})



