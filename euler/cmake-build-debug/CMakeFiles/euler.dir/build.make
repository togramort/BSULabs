# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\prog\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\prog\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\program etc\projects\euler"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\program etc\projects\euler\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/euler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/euler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/euler.dir/flags.make

CMakeFiles/euler.dir/main.cpp.obj: CMakeFiles/euler.dir/flags.make
CMakeFiles/euler.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\program etc\projects\euler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/euler.dir/main.cpp.obj"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\euler.dir\main.cpp.obj -c "D:\program etc\projects\euler\main.cpp"

CMakeFiles/euler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/euler.dir/main.cpp.i"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\program etc\projects\euler\main.cpp" > CMakeFiles\euler.dir\main.cpp.i

CMakeFiles/euler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/euler.dir/main.cpp.s"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\program etc\projects\euler\main.cpp" -o CMakeFiles\euler.dir\main.cpp.s

# Object files for target euler
euler_OBJECTS = \
"CMakeFiles/euler.dir/main.cpp.obj"

# External object files for target euler
euler_EXTERNAL_OBJECTS =

euler.exe: CMakeFiles/euler.dir/main.cpp.obj
euler.exe: CMakeFiles/euler.dir/build.make
euler.exe: CMakeFiles/euler.dir/linklibs.rsp
euler.exe: CMakeFiles/euler.dir/objects1.rsp
euler.exe: CMakeFiles/euler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\program etc\projects\euler\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable euler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\euler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/euler.dir/build: euler.exe

.PHONY : CMakeFiles/euler.dir/build

CMakeFiles/euler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\euler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/euler.dir/clean

CMakeFiles/euler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\program etc\projects\euler" "D:\program etc\projects\euler" "D:\program etc\projects\euler\cmake-build-debug" "D:\program etc\projects\euler\cmake-build-debug" "D:\program etc\projects\euler\cmake-build-debug\CMakeFiles\euler.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/euler.dir/depend

