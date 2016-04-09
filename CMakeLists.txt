cmake_minimum_required(VERSION 3.3)
project(ftpClient)



#set(HUFFMAN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/build)
message(STATUS ${HUFFMAN_INCLUDE_DIRS})


add_subdirectory(Huffman)
add_subdirectory(HW2_FtpClient)
add_subdirectory(HW2_FtpServer)
set(CMAKE_BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)




#include_directories(${PROJECT_SOURCE_DIR}/Huffman/include)



