# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/jackson/gba/arm-core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jackson/gba/arm-core

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jackson/gba/arm-core/CMakeFiles /home/jackson/gba/arm-core//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jackson/gba/arm-core/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named arm_core

# Build rule for target.
arm_core: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 arm_core
.PHONY : arm_core

# fast build rule for target.
arm_core/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/build
.PHONY : arm_core/fast

# target to build an object file
src/alu.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/alu.o
.PHONY : src/alu.o

# target to preprocess a source file
src/alu.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/alu.i
.PHONY : src/alu.i

# target to generate assembly for a file
src/alu.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/alu.s
.PHONY : src/alu.s

# target to build an object file
src/barrel_shifter.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/barrel_shifter.o
.PHONY : src/barrel_shifter.o

# target to preprocess a source file
src/barrel_shifter.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/barrel_shifter.i
.PHONY : src/barrel_shifter.i

# target to generate assembly for a file
src/barrel_shifter.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/barrel_shifter.s
.PHONY : src/barrel_shifter.s

# target to build an object file
src/constants.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/constants.o
.PHONY : src/constants.o

# target to preprocess a source file
src/constants.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/constants.i
.PHONY : src/constants.i

# target to generate assembly for a file
src/constants.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/constants.s
.PHONY : src/constants.s

# target to build an object file
src/cpu.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/cpu.o
.PHONY : src/cpu.o

# target to preprocess a source file
src/cpu.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/cpu.i
.PHONY : src/cpu.i

# target to generate assembly for a file
src/cpu.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/cpu.s
.PHONY : src/cpu.s

# target to build an object file
src/instruction.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/instruction.o
.PHONY : src/instruction.o

# target to preprocess a source file
src/instruction.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/instruction.i
.PHONY : src/instruction.i

# target to generate assembly for a file
src/instruction.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/instruction.s
.PHONY : src/instruction.s

# target to build an object file
src/memory_bus.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/memory_bus.o
.PHONY : src/memory_bus.o

# target to preprocess a source file
src/memory_bus.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/memory_bus.i
.PHONY : src/memory_bus.i

# target to generate assembly for a file
src/memory_bus.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/memory_bus.s
.PHONY : src/memory_bus.s

# target to build an object file
src/multiply.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/multiply.o
.PHONY : src/multiply.o

# target to preprocess a source file
src/multiply.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/multiply.i
.PHONY : src/multiply.i

# target to generate assembly for a file
src/multiply.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/multiply.s
.PHONY : src/multiply.s

# target to build an object file
src/registers.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/registers.o
.PHONY : src/registers.o

# target to preprocess a source file
src/registers.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/registers.i
.PHONY : src/registers.i

# target to generate assembly for a file
src/registers.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/registers.s
.PHONY : src/registers.s

# target to build an object file
src/utils.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/utils.o
.PHONY : src/utils.o

# target to preprocess a source file
src/utils.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/utils.i
.PHONY : src/utils.i

# target to generate assembly for a file
src/utils.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/arm_core.dir/build.make CMakeFiles/arm_core.dir/src/utils.s
.PHONY : src/utils.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... arm_core"
	@echo "... src/alu.o"
	@echo "... src/alu.i"
	@echo "... src/alu.s"
	@echo "... src/barrel_shifter.o"
	@echo "... src/barrel_shifter.i"
	@echo "... src/barrel_shifter.s"
	@echo "... src/constants.o"
	@echo "... src/constants.i"
	@echo "... src/constants.s"
	@echo "... src/cpu.o"
	@echo "... src/cpu.i"
	@echo "... src/cpu.s"
	@echo "... src/instruction.o"
	@echo "... src/instruction.i"
	@echo "... src/instruction.s"
	@echo "... src/memory_bus.o"
	@echo "... src/memory_bus.i"
	@echo "... src/memory_bus.s"
	@echo "... src/multiply.o"
	@echo "... src/multiply.i"
	@echo "... src/multiply.s"
	@echo "... src/registers.o"
	@echo "... src/registers.i"
	@echo "... src/registers.s"
	@echo "... src/utils.o"
	@echo "... src/utils.i"
	@echo "... src/utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

