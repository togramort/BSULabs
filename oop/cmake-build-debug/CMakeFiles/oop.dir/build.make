# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
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
CMAKE_SOURCE_DIR = "D:\program etc\projects\oop"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\program etc\projects\oop\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/oop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/oop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oop.dir/flags.make

CMakeFiles/oop.dir/main.cpp.obj: CMakeFiles/oop.dir/flags.make
CMakeFiles/oop.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\program etc\projects\oop\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/oop.dir/main.cpp.obj"
	D:\prog\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\oop.dir\main.cpp.obj -c "D:\program etc\projects\oop\main.cpp"

CMakeFiles/oop.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oop.dir/main.cpp.i"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\program etc\projects\oop\main.cpp" > CMakeFiles\oop.dir\main.cpp.i

CMakeFiles/oop.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oop.dir/main.cpp.s"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\program etc\projects\oop\main.cpp" -o CMakeFiles\oop.dir\main.cpp.s

CMakeFiles/oop.dir/point2d.cpp.obj: CMakeFiles/oop.dir/flags.make
CMakeFiles/oop.dir/point2d.cpp.obj: ../point2d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\program etc\projects\oop\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/oop.dir/point2d.cpp.obj"
	D:\prog\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\oop.dir\point2d.cpp.obj -c "D:\program etc\projects\oop\point2d.cpp"

CMakeFiles/oop.dir/point2d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oop.dir/point2d.cpp.i"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\program etc\projects\oop\point2d.cpp" > CMakeFiles\oop.dir\point2d.cpp.i

CMakeFiles/oop.dir/point2d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oop.dir/point2d.cpp.s"
	D:\prog\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\program etc\projects\oop\point2d.cpp" -o CMakeFiles\oop.dir\point2d.cpp.s

# Object files for target oop
oop_OBJECTS = \
"CMakeFiles/oop.dir/main.cpp.obj" \
"CMakeFiles/oop.dir/point2d.cpp.obj"

# External object files for target oop
oop_EXTERNAL_OBJECTS =

oop.exe: CMakeFiles/oop.dir/main.cpp.obj
oop.exe: CMakeFiles/oop.dir/point2d.cpp.obj
oop.exe: CMakeFiles/oop.dir/build.make
oop.exe: CMakeFiles/oop.dir/linklibs.rsp
oop.exe: CMakeFiles/oop.dir/objects1.rsp
oop.exe: CMakeFiles/oop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\program etc\projects\oop\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable oop.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\oop.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oop.dir/build: oop.exe

.PHONY : CMakeFiles/oop.dir/build

CMakeFiles/oop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\oop.dir\cmake_clean.cmake
.PHONY : CMakeFiles/oop.dir/clean

CMakeFiles/oop.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\program etc\projects\oop" "D:\program etc\projects\oop" "D:\program etc\projects\oop\cmake-build-debug" "D:\program etc\projects\oop\cmake-build-debug" "D:\program etc\projects\oop\cmake-build-debug\CMakeFiles\oop.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/oop.dir/depend

