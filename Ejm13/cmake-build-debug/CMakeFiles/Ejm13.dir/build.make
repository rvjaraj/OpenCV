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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\vinic\Documents\IAII\OpenCV\Ejm13

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ejm13.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ejm13.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ejm13.dir/flags.make

CMakeFiles/Ejm13.dir/Principal.cpp.obj: CMakeFiles/Ejm13.dir/flags.make
CMakeFiles/Ejm13.dir/Principal.cpp.obj: CMakeFiles/Ejm13.dir/includes_CXX.rsp
CMakeFiles/Ejm13.dir/Principal.cpp.obj: ../Principal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ejm13.dir/Principal.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Ejm13.dir\Principal.cpp.obj -c C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\Principal.cpp

CMakeFiles/Ejm13.dir/Principal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ejm13.dir/Principal.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\Principal.cpp > CMakeFiles\Ejm13.dir\Principal.cpp.i

CMakeFiles/Ejm13.dir/Principal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ejm13.dir/Principal.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\Principal.cpp -o CMakeFiles\Ejm13.dir\Principal.cpp.s

# Object files for target Ejm13
Ejm13_OBJECTS = \
"CMakeFiles/Ejm13.dir/Principal.cpp.obj"

# External object files for target Ejm13
Ejm13_EXTERNAL_OBJECTS =

Ejm13.exe: CMakeFiles/Ejm13.dir/Principal.cpp.obj
Ejm13.exe: CMakeFiles/Ejm13.dir/build.make
Ejm13.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_highgui451.dll.a
Ejm13.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_videoio451.dll.a
Ejm13.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_imgcodecs451.dll.a
Ejm13.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_imgproc451.dll.a
Ejm13.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_core451.dll.a
Ejm13.exe: CMakeFiles/Ejm13.dir/linklibs.rsp
Ejm13.exe: CMakeFiles/Ejm13.dir/objects1.rsp
Ejm13.exe: CMakeFiles/Ejm13.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Ejm13.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Ejm13.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ejm13.dir/build: Ejm13.exe

.PHONY : CMakeFiles/Ejm13.dir/build

CMakeFiles/Ejm13.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Ejm13.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Ejm13.dir/clean

CMakeFiles/Ejm13.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\vinic\Documents\IAII\OpenCV\Ejm13 C:\Users\vinic\Documents\IAII\OpenCV\Ejm13 C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug C:\Users\vinic\Documents\IAII\OpenCV\Ejm13\cmake-build-debug\CMakeFiles\Ejm13.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ejm13.dir/depend

