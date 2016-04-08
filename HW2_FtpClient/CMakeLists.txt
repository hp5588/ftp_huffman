cmake_minimum_required(VERSION 3.3)
project(ftpClient)


include_directories(${HUFFMAN_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES
        main.cpp
        src/FTPClient.cpp
        src/FTPClient.h
        src/FTP.h
        src/tools/Command.cpp
        src/tools/Command.h

        )

add_executable(ftpClient ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Huffman)
