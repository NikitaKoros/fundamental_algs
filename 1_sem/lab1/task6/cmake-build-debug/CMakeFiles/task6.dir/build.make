# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nikita/fund_algs/fundamental_algs/lab1/task6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/task6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/task6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task6.dir/flags.make

CMakeFiles/task6.dir/task6.c.o: CMakeFiles/task6.dir/flags.make
CMakeFiles/task6.dir/task6.c.o: /home/nikita/fund_algs/fundamental_algs/lab1/task6/task6.c
CMakeFiles/task6.dir/task6.c.o: CMakeFiles/task6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task6.dir/task6.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/task6.dir/task6.c.o -MF CMakeFiles/task6.dir/task6.c.o.d -o CMakeFiles/task6.dir/task6.c.o -c /home/nikita/fund_algs/fundamental_algs/lab1/task6/task6.c

CMakeFiles/task6.dir/task6.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/task6.dir/task6.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nikita/fund_algs/fundamental_algs/lab1/task6/task6.c > CMakeFiles/task6.dir/task6.c.i

CMakeFiles/task6.dir/task6.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/task6.dir/task6.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nikita/fund_algs/fundamental_algs/lab1/task6/task6.c -o CMakeFiles/task6.dir/task6.c.s

CMakeFiles/task6.dir/util_task6.c.o: CMakeFiles/task6.dir/flags.make
CMakeFiles/task6.dir/util_task6.c.o: /home/nikita/fund_algs/fundamental_algs/lab1/task6/util_task6.c
CMakeFiles/task6.dir/util_task6.c.o: CMakeFiles/task6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/task6.dir/util_task6.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/task6.dir/util_task6.c.o -MF CMakeFiles/task6.dir/util_task6.c.o.d -o CMakeFiles/task6.dir/util_task6.c.o -c /home/nikita/fund_algs/fundamental_algs/lab1/task6/util_task6.c

CMakeFiles/task6.dir/util_task6.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/task6.dir/util_task6.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nikita/fund_algs/fundamental_algs/lab1/task6/util_task6.c > CMakeFiles/task6.dir/util_task6.c.i

CMakeFiles/task6.dir/util_task6.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/task6.dir/util_task6.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nikita/fund_algs/fundamental_algs/lab1/task6/util_task6.c -o CMakeFiles/task6.dir/util_task6.c.s

CMakeFiles/task6.dir/integrals.c.o: CMakeFiles/task6.dir/flags.make
CMakeFiles/task6.dir/integrals.c.o: /home/nikita/fund_algs/fundamental_algs/lab1/task6/integrals.c
CMakeFiles/task6.dir/integrals.c.o: CMakeFiles/task6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/task6.dir/integrals.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/task6.dir/integrals.c.o -MF CMakeFiles/task6.dir/integrals.c.o.d -o CMakeFiles/task6.dir/integrals.c.o -c /home/nikita/fund_algs/fundamental_algs/lab1/task6/integrals.c

CMakeFiles/task6.dir/integrals.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/task6.dir/integrals.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nikita/fund_algs/fundamental_algs/lab1/task6/integrals.c > CMakeFiles/task6.dir/integrals.c.i

CMakeFiles/task6.dir/integrals.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/task6.dir/integrals.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nikita/fund_algs/fundamental_algs/lab1/task6/integrals.c -o CMakeFiles/task6.dir/integrals.c.s

# Object files for target task6
task6_OBJECTS = \
"CMakeFiles/task6.dir/task6.c.o" \
"CMakeFiles/task6.dir/util_task6.c.o" \
"CMakeFiles/task6.dir/integrals.c.o"

# External object files for target task6
task6_EXTERNAL_OBJECTS =

task6: CMakeFiles/task6.dir/task6.c.o
task6: CMakeFiles/task6.dir/util_task6.c.o
task6: CMakeFiles/task6.dir/integrals.c.o
task6: CMakeFiles/task6.dir/build.make
task6: CMakeFiles/task6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable task6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task6.dir/build: task6
.PHONY : CMakeFiles/task6.dir/build

CMakeFiles/task6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task6.dir/clean

CMakeFiles/task6.dir/depend:
	cd /home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikita/fund_algs/fundamental_algs/lab1/task6 /home/nikita/fund_algs/fundamental_algs/lab1/task6 /home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug /home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug /home/nikita/fund_algs/fundamental_algs/lab1/task6/cmake-build-debug/CMakeFiles/task6.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/task6.dir/depend

