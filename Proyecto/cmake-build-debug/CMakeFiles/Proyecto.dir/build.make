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
CMAKE_SOURCE_DIR = C:\Users\vinic\Documents\IAII\OpenCV\Proyecto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Proyecto.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Proyecto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Proyecto.dir/flags.make

CMakeFiles/Proyecto.dir/mai2.cpp.obj: CMakeFiles/Proyecto.dir/flags.make
CMakeFiles/Proyecto.dir/mai2.cpp.obj: CMakeFiles/Proyecto.dir/includes_CXX.rsp
CMakeFiles/Proyecto.dir/mai2.cpp.obj: ../mai2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Proyecto.dir/mai2.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Proyecto.dir\mai2.cpp.obj -c C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\mai2.cpp

CMakeFiles/Proyecto.dir/mai2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto.dir/mai2.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\mai2.cpp > CMakeFiles\Proyecto.dir\mai2.cpp.i

CMakeFiles/Proyecto.dir/mai2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto.dir/mai2.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\mai2.cpp -o CMakeFiles\Proyecto.dir\mai2.cpp.s

CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj: CMakeFiles/Proyecto.dir/flags.make
CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj: CMakeFiles/Proyecto.dir/includes_CXX.rsp
CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj: ../Procesamiento.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Proyecto.dir\Procesamiento.cpp.obj -c C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\Procesamiento.cpp

CMakeFiles/Proyecto.dir/Procesamiento.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto.dir/Procesamiento.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\Procesamiento.cpp > CMakeFiles\Proyecto.dir\Procesamiento.cpp.i

CMakeFiles/Proyecto.dir/Procesamiento.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto.dir/Procesamiento.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\Procesamiento.cpp -o CMakeFiles\Proyecto.dir\Procesamiento.cpp.s

# Object files for target Proyecto
Proyecto_OBJECTS = \
"CMakeFiles/Proyecto.dir/mai2.cpp.obj" \
"CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj"

# External object files for target Proyecto
Proyecto_EXTERNAL_OBJECTS =

Proyecto.exe: CMakeFiles/Proyecto.dir/mai2.cpp.obj
Proyecto.exe: CMakeFiles/Proyecto.dir/Procesamiento.cpp.obj
Proyecto.exe: CMakeFiles/Proyecto.dir/build.make
Proyecto.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_highgui451.dll.a
Proyecto.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_videoio451.dll.a
Proyecto.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_imgcodecs451.dll.a
Proyecto.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_imgproc451.dll.a
Proyecto.exe: C:/openCV/mingw-build/install/x64/mingw/lib/libopencv_core451.dll.a
Proyecto.exe: CMakeFiles/Proyecto.dir/linklibs.rsp
Proyecto.exe: CMakeFiles/Proyecto.dir/objects1.rsp
Proyecto.exe: CMakeFiles/Proyecto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Proyecto.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Proyecto.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Proyecto.dir/build: Proyecto.exe

.PHONY : CMakeFiles/Proyecto.dir/build

CMakeFiles/Proyecto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Proyecto.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Proyecto.dir/clean

CMakeFiles/Proyecto.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\vinic\Documents\IAII\OpenCV\Proyecto C:\Users\vinic\Documents\IAII\OpenCV\Proyecto C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug C:\Users\vinic\Documents\IAII\OpenCV\Proyecto\cmake-build-debug\CMakeFiles\Proyecto.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Proyecto.dir/depend

