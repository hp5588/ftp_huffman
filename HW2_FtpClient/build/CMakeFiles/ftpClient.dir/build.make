# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/brian/software/cmake-3.5.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/brian/software/cmake-3.5.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brian/git/HW2_FtpClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brian/git/HW2_FtpClient/build

# Include any dependencies generated for this target.
include CMakeFiles/ftpClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ftpClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ftpClient.dir/flags.make

CMakeFiles/ftpClient.dir/main.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ftpClient.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/main.cpp.o -c /home/brian/git/HW2_FtpClient/main.cpp

CMakeFiles/ftpClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/main.cpp > CMakeFiles/ftpClient.dir/main.cpp.i

CMakeFiles/ftpClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/main.cpp -o CMakeFiles/ftpClient.dir/main.cpp.s

CMakeFiles/ftpClient.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/main.cpp.o.requires

CMakeFiles/ftpClient.dir/main.cpp.o.provides: CMakeFiles/ftpClient.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/main.cpp.o.provides

CMakeFiles/ftpClient.dir/main.cpp.o.provides.build: CMakeFiles/ftpClient.dir/main.cpp.o


CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o: ../src/FTPClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o -c /home/brian/git/HW2_FtpClient/src/FTPClient.cpp

CMakeFiles/ftpClient.dir/src/FTPClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/src/FTPClient.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/src/FTPClient.cpp > CMakeFiles/ftpClient.dir/src/FTPClient.cpp.i

CMakeFiles/ftpClient.dir/src/FTPClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/src/FTPClient.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/src/FTPClient.cpp -o CMakeFiles/ftpClient.dir/src/FTPClient.cpp.s

CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.requires

CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.provides: CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.provides

CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.provides.build: CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o


CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o: ../src/tools/Command.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o -c /home/brian/git/HW2_FtpClient/src/tools/Command.cpp

CMakeFiles/ftpClient.dir/src/tools/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/src/tools/Command.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/src/tools/Command.cpp > CMakeFiles/ftpClient.dir/src/tools/Command.cpp.i

CMakeFiles/ftpClient.dir/src/tools/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/src/tools/Command.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/src/tools/Command.cpp -o CMakeFiles/ftpClient.dir/src/tools/Command.cpp.s

CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.requires

CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.provides: CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.provides

CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.provides.build: CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o


CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o: ../src/huffman/Huffman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o -c /home/brian/git/HW2_FtpClient/src/huffman/Huffman.cpp

CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/src/huffman/Huffman.cpp > CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.i

CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/src/huffman/Huffman.cpp -o CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.s

CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.requires

CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.provides: CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.provides

CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.provides.build: CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o


CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o: ../src/huffman/TreeNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o -c /home/brian/git/HW2_FtpClient/src/huffman/TreeNode.cpp

CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/src/huffman/TreeNode.cpp > CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.i

CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/src/huffman/TreeNode.cpp -o CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.s

CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.requires

CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.provides: CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.provides

CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.provides.build: CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o


CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o: CMakeFiles/ftpClient.dir/flags.make
CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o: ../src/huffman/Tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o -c /home/brian/git/HW2_FtpClient/src/huffman/Tree.cpp

CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brian/git/HW2_FtpClient/src/huffman/Tree.cpp > CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.i

CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brian/git/HW2_FtpClient/src/huffman/Tree.cpp -o CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.s

CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.requires:

.PHONY : CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.requires

CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.provides: CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.requires
	$(MAKE) -f CMakeFiles/ftpClient.dir/build.make CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.provides.build
.PHONY : CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.provides

CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.provides.build: CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o


# Object files for target ftpClient
ftpClient_OBJECTS = \
"CMakeFiles/ftpClient.dir/main.cpp.o" \
"CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o" \
"CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o" \
"CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o" \
"CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o" \
"CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o"

# External object files for target ftpClient
ftpClient_EXTERNAL_OBJECTS =

ftpClient: CMakeFiles/ftpClient.dir/main.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o
ftpClient: CMakeFiles/ftpClient.dir/build.make
ftpClient: CMakeFiles/ftpClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brian/git/HW2_FtpClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ftpClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftpClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ftpClient.dir/build: ftpClient

.PHONY : CMakeFiles/ftpClient.dir/build

CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/main.cpp.o.requires
CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/src/FTPClient.cpp.o.requires
CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/src/tools/Command.cpp.o.requires
CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/src/huffman/Huffman.cpp.o.requires
CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/src/huffman/TreeNode.cpp.o.requires
CMakeFiles/ftpClient.dir/requires: CMakeFiles/ftpClient.dir/src/huffman/Tree.cpp.o.requires

.PHONY : CMakeFiles/ftpClient.dir/requires

CMakeFiles/ftpClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ftpClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ftpClient.dir/clean

CMakeFiles/ftpClient.dir/depend:
	cd /home/brian/git/HW2_FtpClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brian/git/HW2_FtpClient /home/brian/git/HW2_FtpClient /home/brian/git/HW2_FtpClient/build /home/brian/git/HW2_FtpClient/build /home/brian/git/HW2_FtpClient/build/CMakeFiles/ftpClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ftpClient.dir/depend

