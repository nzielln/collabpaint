# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.21.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.21.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin"

# Include any dependencies generated for this target.
include CMakeFiles/App.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/App.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/App.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/App.dir/flags.make

CMakeFiles/App.dir/src/App.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/App.cpp.o: ../src/App.cpp
CMakeFiles/App.dir/src/App.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/App.dir/src/App.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/App.cpp.o -MF CMakeFiles/App.dir/src/App.cpp.o.d -o CMakeFiles/App.dir/src/App.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/App.cpp"

CMakeFiles/App.dir/src/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/App.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/App.cpp" > CMakeFiles/App.dir/src/App.cpp.i

CMakeFiles/App.dir/src/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/App.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/App.cpp" -o CMakeFiles/App.dir/src/App.cpp.s

CMakeFiles/App.dir/src/Draw.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/Draw.cpp.o: ../src/Draw.cpp
CMakeFiles/App.dir/src/Draw.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/App.dir/src/Draw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/Draw.cpp.o -MF CMakeFiles/App.dir/src/Draw.cpp.o.d -o CMakeFiles/App.dir/src/Draw.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Draw.cpp"

CMakeFiles/App.dir/src/Draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/Draw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Draw.cpp" > CMakeFiles/App.dir/src/Draw.cpp.i

CMakeFiles/App.dir/src/Draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/Draw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Draw.cpp" -o CMakeFiles/App.dir/src/Draw.cpp.s

CMakeFiles/App.dir/src/Command.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/Command.cpp.o: ../src/Command.cpp
CMakeFiles/App.dir/src/Command.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/App.dir/src/Command.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/Command.cpp.o -MF CMakeFiles/App.dir/src/Command.cpp.o.d -o CMakeFiles/App.dir/src/Command.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Command.cpp"

CMakeFiles/App.dir/src/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/Command.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Command.cpp" > CMakeFiles/App.dir/src/Command.cpp.i

CMakeFiles/App.dir/src/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/Command.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Command.cpp" -o CMakeFiles/App.dir/src/Command.cpp.s

CMakeFiles/App.dir/src/main.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/App.dir/src/main.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/App.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/main.cpp.o -MF CMakeFiles/App.dir/src/main.cpp.o.d -o CMakeFiles/App.dir/src/main.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/main.cpp"

CMakeFiles/App.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/main.cpp" > CMakeFiles/App.dir/src/main.cpp.i

CMakeFiles/App.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/main.cpp" -o CMakeFiles/App.dir/src/main.cpp.s

CMakeFiles/App.dir/src/DrawStroke.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/DrawStroke.cpp.o: ../src/DrawStroke.cpp
CMakeFiles/App.dir/src/DrawStroke.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/App.dir/src/DrawStroke.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/DrawStroke.cpp.o -MF CMakeFiles/App.dir/src/DrawStroke.cpp.o.d -o CMakeFiles/App.dir/src/DrawStroke.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawStroke.cpp"

CMakeFiles/App.dir/src/DrawStroke.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/DrawStroke.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawStroke.cpp" > CMakeFiles/App.dir/src/DrawStroke.cpp.i

CMakeFiles/App.dir/src/DrawStroke.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/DrawStroke.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawStroke.cpp" -o CMakeFiles/App.dir/src/DrawStroke.cpp.s

CMakeFiles/App.dir/src/ClearScreen.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/ClearScreen.cpp.o: ../src/ClearScreen.cpp
CMakeFiles/App.dir/src/ClearScreen.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/App.dir/src/ClearScreen.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/ClearScreen.cpp.o -MF CMakeFiles/App.dir/src/ClearScreen.cpp.o.d -o CMakeFiles/App.dir/src/ClearScreen.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/ClearScreen.cpp"

CMakeFiles/App.dir/src/ClearScreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/ClearScreen.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/ClearScreen.cpp" > CMakeFiles/App.dir/src/ClearScreen.cpp.i

CMakeFiles/App.dir/src/ClearScreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/ClearScreen.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/ClearScreen.cpp" -o CMakeFiles/App.dir/src/ClearScreen.cpp.s

CMakeFiles/App.dir/src/CompositeCommand.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/CompositeCommand.cpp.o: ../src/CompositeCommand.cpp
CMakeFiles/App.dir/src/CompositeCommand.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/App.dir/src/CompositeCommand.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/CompositeCommand.cpp.o -MF CMakeFiles/App.dir/src/CompositeCommand.cpp.o.d -o CMakeFiles/App.dir/src/CompositeCommand.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/CompositeCommand.cpp"

CMakeFiles/App.dir/src/CompositeCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/CompositeCommand.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/CompositeCommand.cpp" > CMakeFiles/App.dir/src/CompositeCommand.cpp.i

CMakeFiles/App.dir/src/CompositeCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/CompositeCommand.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/CompositeCommand.cpp" -o CMakeFiles/App.dir/src/CompositeCommand.cpp.s

CMakeFiles/App.dir/src/TCPClient.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/TCPClient.cpp.o: ../src/TCPClient.cpp
CMakeFiles/App.dir/src/TCPClient.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/App.dir/src/TCPClient.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/TCPClient.cpp.o -MF CMakeFiles/App.dir/src/TCPClient.cpp.o.d -o CMakeFiles/App.dir/src/TCPClient.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPClient.cpp"

CMakeFiles/App.dir/src/TCPClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/TCPClient.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPClient.cpp" > CMakeFiles/App.dir/src/TCPClient.cpp.i

CMakeFiles/App.dir/src/TCPClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/TCPClient.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPClient.cpp" -o CMakeFiles/App.dir/src/TCPClient.cpp.s

CMakeFiles/App.dir/src/TCPServer.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/TCPServer.cpp.o: ../src/TCPServer.cpp
CMakeFiles/App.dir/src/TCPServer.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/App.dir/src/TCPServer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/TCPServer.cpp.o -MF CMakeFiles/App.dir/src/TCPServer.cpp.o.d -o CMakeFiles/App.dir/src/TCPServer.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPServer.cpp"

CMakeFiles/App.dir/src/TCPServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/TCPServer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPServer.cpp" > CMakeFiles/App.dir/src/TCPServer.cpp.i

CMakeFiles/App.dir/src/TCPServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/TCPServer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/TCPServer.cpp" -o CMakeFiles/App.dir/src/TCPServer.cpp.s

CMakeFiles/App.dir/src/Eraser.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/Eraser.cpp.o: ../src/Eraser.cpp
CMakeFiles/App.dir/src/Eraser.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/App.dir/src/Eraser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/Eraser.cpp.o -MF CMakeFiles/App.dir/src/Eraser.cpp.o.d -o CMakeFiles/App.dir/src/Eraser.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Eraser.cpp"

CMakeFiles/App.dir/src/Eraser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/Eraser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Eraser.cpp" > CMakeFiles/App.dir/src/Eraser.cpp.i

CMakeFiles/App.dir/src/Eraser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/Eraser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/Eraser.cpp" -o CMakeFiles/App.dir/src/Eraser.cpp.s

CMakeFiles/App.dir/src/EraserStroke.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/EraserStroke.cpp.o: ../src/EraserStroke.cpp
CMakeFiles/App.dir/src/EraserStroke.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/App.dir/src/EraserStroke.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/EraserStroke.cpp.o -MF CMakeFiles/App.dir/src/EraserStroke.cpp.o.d -o CMakeFiles/App.dir/src/EraserStroke.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/EraserStroke.cpp"

CMakeFiles/App.dir/src/EraserStroke.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/EraserStroke.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/EraserStroke.cpp" > CMakeFiles/App.dir/src/EraserStroke.cpp.i

CMakeFiles/App.dir/src/EraserStroke.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/EraserStroke.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/EraserStroke.cpp" -o CMakeFiles/App.dir/src/EraserStroke.cpp.s

CMakeFiles/App.dir/src/BrushStroke.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/BrushStroke.cpp.o: ../src/BrushStroke.cpp
CMakeFiles/App.dir/src/BrushStroke.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/App.dir/src/BrushStroke.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/BrushStroke.cpp.o -MF CMakeFiles/App.dir/src/BrushStroke.cpp.o.d -o CMakeFiles/App.dir/src/BrushStroke.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/BrushStroke.cpp"

CMakeFiles/App.dir/src/BrushStroke.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/BrushStroke.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/BrushStroke.cpp" > CMakeFiles/App.dir/src/BrushStroke.cpp.i

CMakeFiles/App.dir/src/BrushStroke.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/BrushStroke.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/BrushStroke.cpp" -o CMakeFiles/App.dir/src/BrushStroke.cpp.s

CMakeFiles/App.dir/src/DrawBrush.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/src/DrawBrush.cpp.o: ../src/DrawBrush.cpp
CMakeFiles/App.dir/src/DrawBrush.cpp.o: CMakeFiles/App.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/App.dir/src/DrawBrush.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/App.dir/src/DrawBrush.cpp.o -MF CMakeFiles/App.dir/src/DrawBrush.cpp.o.d -o CMakeFiles/App.dir/src/DrawBrush.cpp.o -c "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawBrush.cpp"

CMakeFiles/App.dir/src/DrawBrush.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/src/DrawBrush.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawBrush.cpp" > CMakeFiles/App.dir/src/DrawBrush.cpp.i

CMakeFiles/App.dir/src/DrawBrush.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/src/DrawBrush.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/src/DrawBrush.cpp" -o CMakeFiles/App.dir/src/DrawBrush.cpp.s

# Object files for target App
App_OBJECTS = \
"CMakeFiles/App.dir/src/App.cpp.o" \
"CMakeFiles/App.dir/src/Draw.cpp.o" \
"CMakeFiles/App.dir/src/Command.cpp.o" \
"CMakeFiles/App.dir/src/main.cpp.o" \
"CMakeFiles/App.dir/src/DrawStroke.cpp.o" \
"CMakeFiles/App.dir/src/ClearScreen.cpp.o" \
"CMakeFiles/App.dir/src/CompositeCommand.cpp.o" \
"CMakeFiles/App.dir/src/TCPClient.cpp.o" \
"CMakeFiles/App.dir/src/TCPServer.cpp.o" \
"CMakeFiles/App.dir/src/Eraser.cpp.o" \
"CMakeFiles/App.dir/src/EraserStroke.cpp.o" \
"CMakeFiles/App.dir/src/BrushStroke.cpp.o" \
"CMakeFiles/App.dir/src/DrawBrush.cpp.o"

# External object files for target App
App_EXTERNAL_OBJECTS =

App: CMakeFiles/App.dir/src/App.cpp.o
App: CMakeFiles/App.dir/src/Draw.cpp.o
App: CMakeFiles/App.dir/src/Command.cpp.o
App: CMakeFiles/App.dir/src/main.cpp.o
App: CMakeFiles/App.dir/src/DrawStroke.cpp.o
App: CMakeFiles/App.dir/src/ClearScreen.cpp.o
App: CMakeFiles/App.dir/src/CompositeCommand.cpp.o
App: CMakeFiles/App.dir/src/TCPClient.cpp.o
App: CMakeFiles/App.dir/src/TCPServer.cpp.o
App: CMakeFiles/App.dir/src/Eraser.cpp.o
App: CMakeFiles/App.dir/src/EraserStroke.cpp.o
App: CMakeFiles/App.dir/src/BrushStroke.cpp.o
App: CMakeFiles/App.dir/src/DrawBrush.cpp.o
App: CMakeFiles/App.dir/build.make
App: _deps/sfml-build/lib/libsfml-graphics-d.2.5.1.dylib
App: _deps/sfml-build/lib/libsfml-network-d.2.5.1.dylib
App: _deps/sfml-build/lib/libsfml-window-d.2.5.1.dylib
App: _deps/sfml-build/lib/libsfml-system-d.2.5.1.dylib
App: CMakeFiles/App.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable App"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/App.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/App.dir/build: App
.PHONY : CMakeFiles/App.dir/build

CMakeFiles/App.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/App.dir/cmake_clean.cmake
.PHONY : CMakeFiles/App.dir/clean

CMakeFiles/App.dir/depend:
	cd "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject" "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject" "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin" "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin" "/Users/nzielln/Desktop/Past Semesters/Fall 2021/SWE/finalproject-team-16/FinalProject/bin/CMakeFiles/App.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/App.dir/depend

