# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "C:/Program Files/JetBrains/CLion 2022.1.1/bin/cmake/win/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/JetBrains/CLion 2022.1.1/bin/cmake/win/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/file/cpu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/file/cpu/build

# Include any dependencies generated for this target.
include CMakeFiles/cpu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cpu.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cpu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpu.dir/flags.make

CMakeFiles/cpu.dir/main.c.obj: CMakeFiles/cpu.dir/flags.make
CMakeFiles/cpu.dir/main.c.obj: D:/file/cpu/main.c
CMakeFiles/cpu.dir/main.c.obj: CMakeFiles/cpu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/file/cpu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cpu.dir/main.c.obj"
	C:/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cpu.dir/main.c.obj -MF CMakeFiles/cpu.dir/main.c.obj.d -o CMakeFiles/cpu.dir/main.c.obj -c D:/file/cpu/main.c

CMakeFiles/cpu.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cpu.dir/main.c.i"
	C:/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/file/cpu/main.c > CMakeFiles/cpu.dir/main.c.i

CMakeFiles/cpu.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cpu.dir/main.c.s"
	C:/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/file/cpu/main.c -o CMakeFiles/cpu.dir/main.c.s

# Object files for target cpu
cpu_OBJECTS = \
"CMakeFiles/cpu.dir/main.c.obj"

# External object files for target cpu
cpu_EXTERNAL_OBJECTS =

cpu.exe: CMakeFiles/cpu.dir/main.c.obj
cpu.exe: CMakeFiles/cpu.dir/build.make
cpu.exe: CMakeFiles/cpu.dir/linklibs.rsp
cpu.exe: CMakeFiles/cpu.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/file/cpu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cpu.exe"
	"C:/Program Files/JetBrains/CLion 2022.1.1/bin/cmake/win/bin/cmake.exe" -E rm -f CMakeFiles/cpu.dir/objects.a
	C:/w64devkit/bin/ar.exe qc CMakeFiles/cpu.dir/objects.a @CMakeFiles/cpu.dir/objects1.rsp
	C:/w64devkit/bin/gcc.exe -g -Wl,--whole-archive CMakeFiles/cpu.dir/objects.a -Wl,--no-whole-archive -o cpu.exe -Wl,--out-implib,libcpu.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/cpu.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/cpu.dir/build: cpu.exe
.PHONY : CMakeFiles/cpu.dir/build

CMakeFiles/cpu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpu.dir/clean

CMakeFiles/cpu.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/file/cpu D:/file/cpu D:/file/cpu/build D:/file/cpu/build D:/file/cpu/build/CMakeFiles/cpu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpu.dir/depend

