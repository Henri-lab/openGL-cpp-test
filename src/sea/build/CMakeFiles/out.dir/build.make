# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/henrifox/_code_source_/opengl_code/src/sea

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/henrifox/_code_source_/opengl_code/src/sea/build

# Include any dependencies generated for this target.
include CMakeFiles/out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/out.dir/flags.make

CMakeFiles/out.dir/sea.cpp.o: CMakeFiles/out.dir/flags.make
CMakeFiles/out.dir/sea.cpp.o: /Users/henrifox/_code_source_/opengl_code/src/sea/sea.cpp
CMakeFiles/out.dir/sea.cpp.o: CMakeFiles/out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/henrifox/_code_source_/opengl_code/src/sea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/out.dir/sea.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/out.dir/sea.cpp.o -MF CMakeFiles/out.dir/sea.cpp.o.d -o CMakeFiles/out.dir/sea.cpp.o -c /Users/henrifox/_code_source_/opengl_code/src/sea/sea.cpp

CMakeFiles/out.dir/sea.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/out.dir/sea.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henrifox/_code_source_/opengl_code/src/sea/sea.cpp > CMakeFiles/out.dir/sea.cpp.i

CMakeFiles/out.dir/sea.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/out.dir/sea.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henrifox/_code_source_/opengl_code/src/sea/sea.cpp -o CMakeFiles/out.dir/sea.cpp.s

CMakeFiles/out.dir/utils/read.cpp.o: CMakeFiles/out.dir/flags.make
CMakeFiles/out.dir/utils/read.cpp.o: /Users/henrifox/_code_source_/opengl_code/src/sea/utils/read.cpp
CMakeFiles/out.dir/utils/read.cpp.o: CMakeFiles/out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/henrifox/_code_source_/opengl_code/src/sea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/out.dir/utils/read.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/out.dir/utils/read.cpp.o -MF CMakeFiles/out.dir/utils/read.cpp.o.d -o CMakeFiles/out.dir/utils/read.cpp.o -c /Users/henrifox/_code_source_/opengl_code/src/sea/utils/read.cpp

CMakeFiles/out.dir/utils/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/out.dir/utils/read.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henrifox/_code_source_/opengl_code/src/sea/utils/read.cpp > CMakeFiles/out.dir/utils/read.cpp.i

CMakeFiles/out.dir/utils/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/out.dir/utils/read.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henrifox/_code_source_/opengl_code/src/sea/utils/read.cpp -o CMakeFiles/out.dir/utils/read.cpp.s

CMakeFiles/out.dir/utils/shader.cpp.o: CMakeFiles/out.dir/flags.make
CMakeFiles/out.dir/utils/shader.cpp.o: /Users/henrifox/_code_source_/opengl_code/src/sea/utils/shader.cpp
CMakeFiles/out.dir/utils/shader.cpp.o: CMakeFiles/out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/henrifox/_code_source_/opengl_code/src/sea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/out.dir/utils/shader.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/out.dir/utils/shader.cpp.o -MF CMakeFiles/out.dir/utils/shader.cpp.o.d -o CMakeFiles/out.dir/utils/shader.cpp.o -c /Users/henrifox/_code_source_/opengl_code/src/sea/utils/shader.cpp

CMakeFiles/out.dir/utils/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/out.dir/utils/shader.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/henrifox/_code_source_/opengl_code/src/sea/utils/shader.cpp > CMakeFiles/out.dir/utils/shader.cpp.i

CMakeFiles/out.dir/utils/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/out.dir/utils/shader.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/henrifox/_code_source_/opengl_code/src/sea/utils/shader.cpp -o CMakeFiles/out.dir/utils/shader.cpp.s

# Object files for target out
out_OBJECTS = \
"CMakeFiles/out.dir/sea.cpp.o" \
"CMakeFiles/out.dir/utils/read.cpp.o" \
"CMakeFiles/out.dir/utils/shader.cpp.o"

# External object files for target out
out_EXTERNAL_OBJECTS =

out: CMakeFiles/out.dir/sea.cpp.o
out: CMakeFiles/out.dir/utils/read.cpp.o
out: CMakeFiles/out.dir/utils/shader.cpp.o
out: CMakeFiles/out.dir/build.make
out: /opt/homebrew/lib/libglfw.3.4.dylib
out: /opt/homebrew/lib/libGLEW.2.2.0.dylib
out: CMakeFiles/out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/henrifox/_code_source_/opengl_code/src/sea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/out.dir/build: out
.PHONY : CMakeFiles/out.dir/build

CMakeFiles/out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/out.dir/clean

CMakeFiles/out.dir/depend:
	cd /Users/henrifox/_code_source_/opengl_code/src/sea/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/henrifox/_code_source_/opengl_code/src/sea /Users/henrifox/_code_source_/opengl_code/src/sea /Users/henrifox/_code_source_/opengl_code/src/sea/build /Users/henrifox/_code_source_/opengl_code/src/sea/build /Users/henrifox/_code_source_/opengl_code/src/sea/build/CMakeFiles/out.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/out.dir/depend

