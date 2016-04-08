cmake_minimum_required(VERSION 3.3)
project(ftpServer)


include_directories(${HUFFMAN_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#[[set(SOURCE_FILES
        main.cpp
        src/Server.cpp
        src/Server.h
        src/FTP.h
        src/tools/Command.cpp
        src/tools/Command.h
        src/huffman/Huffman.h
        src/huffman/Huffman.cpp
        src/huffman/TreeNode.h
        src/huffman/TreeNode.cpp
        )]]

set(SOURCE_FILES
        main.cpp
        src/Server.cpp
        src/Server.h
        src/FTP.h
        src/tools/Command.cpp
        src/tools/Command.h

        )


add_executable(ftpServer ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Huffman)
