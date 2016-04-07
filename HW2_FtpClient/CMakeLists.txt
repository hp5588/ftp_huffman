cmake_minimum_required(VERSION 3.3)
project(ftpClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/FTPClient.cpp
        src/FTPClient.h
        src/FTP.h
        src/tools/Command.cpp
        src/tools/Command.h
#[[        src/huffman/Huffman.cpp
        src/huffman/Huffman.h
        src/huffman/TreeNode.cpp
        src/huffman/TreeNode.h
        src/huffman/Tree.cpp
        src/huffman/Tree.h]]
        )
include_directories(${HUFFMAN_INCLUDE_DIRS})

add_executable(ftpClient ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Huffman)
