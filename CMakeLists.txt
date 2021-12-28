# The file always start with cmake_minimum_required to define
# which version of CMake is used.
cmake_minimum_required(VERSION 3.14.0)
# Note: We need at least version 3.14 for the FetchContent Module


set(CMAKE_BUILD_TYPE Debug)

# Next we set the project name
project(Collaborative_Paint
        VERSION 1.0
        LANGUAGES CXX) # work in C++

# Set the language standard
set(CMAKE_CXX_STANDARD 20)

# EN - For building on Mac M1
if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "macOS architecture to build; 64-bit is expected" FORCE)
endif()

find_package(OpenGL REQUIRED)
# Print out the path for debugging purposes
message(STATUS "Found OpenGL at path: ${OPENGL_INCLUDE_DIR}")

# This is the executable that we are going to make
# It will have the correct extension for the platform(.exe, .app, etc.)
# that we are compiling on.
# We also want to specify all of the source files that we will be using.
add_executable(App ./src/App.cpp ./src/Draw.cpp ./src/Command.cpp ./src/main.cpp ./src/DrawStroke.cpp ./src/ClearScreen.cpp ./src/CompositeCommand.cpp ./src/TCPClient.cpp ./src/TCPServer.cpp ./src/Eraser.cpp ./include/EraserStroke.hpp ./src/EraserStroke.cpp ./src/BrushStroke.cpp ./include/BrushStroke.hpp ./src/DrawBrush.cpp ./include/DrawBrush.hpp ./include/EraserStroke.hpp ./include/Eraser.hpp ./src/Eraser.cpp ./src/EraserStroke.cpp)
add_executable(App_Test ./src/App.cpp ./src/Draw.cpp ./src/Command.cpp ./src/DrawStroke.cpp ./src/ClearScreen.cpp ./src/CompositeCommand.cpp ./src/TCPClient.cpp ./src/TCPServer.cpp ./src/Eraser.cpp ./include/EraserStroke.hpp ./src/EraserStroke.cpp ./src/BrushStroke.cpp ./include/BrushStroke.hpp ./src/DrawBrush.cpp ./include/DrawBrush.hpp ./include/EraserStroke.hpp ./include/Eraser.hpp ./src/Eraser.cpp ./src/EraserStroke.cpp ./tests/main_test.cpp ./tests/catch_amalgamated.cpp)

# Add any command line compilation options
target_compile_options(App PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(App_Test PRIVATE -Wall -Wextra -Wpedantic)

include_directories("./include")

# Find or populate SFML and link
#find_library(LIBRARY_SFML sfml)
if(LIBRARY_SFML)
    target_link_libraries(App PRIVATE ${LIBRARY_SFML})
    target_link_libraries(App_Test PRIVATE ${LIBRARY_SFML})
else()
    message("Could not find LIBRARY_SFML--attempting to build it")
    set(SFML_VERSION "2.5.1")
    include(FetchContent)
    FetchContent_Declare(sfml
            GIT_REPOSITORY "https://github.com/SFML/SFML.git"
            GIT_TAG "${SFML_VERSION}")
    FetchContent_GetProperties(sfml)
    if(NOT sfml_POPULATED)
        message("Attempting to populate sfml")
        FetchContent_Populate(sfml)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
        # Now try to link the libraries
    endif()
endif()

# Which packages do we need to find
#find_package(SFML REQUIRED COMPONENTS network window graphics system)

# Where to find our header files
include_directories(SYSTEM "./_deps/sfml-src/include")

# Tell SFML which directory to find our libraries
link_directories(SYSTEM "./_deps/sfml-build/lib/")

include_directories(${OPENGL_INCLUDE_DIR})

# Which of the directories (in the above folder) to actually link
target_link_libraries(App
        PRIVATE SYSTEM
        sfml-window
        sfml-system
        sfml-graphics
        sfml-network
        ${OPENGL_LIBRARY}
        )

target_link_libraries(App_Test
        PRIVATE SYSTEM
        sfml-window
        sfml-system
        sfml-graphics
        sfml-network
        ${OPENGL_LIBRARY}
        )

# If you want you can manually check what platform you are on with
message("======================")
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("Building on windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("Building on Linux")
    message("Note: For SFML, Linux may require you to download many dependencies from scratch")
    message("e.g., sudo apt-get install -y libfreetype6-dev")
    message("      sudo apt-get install -y libopenal-dev")
    message("      sudo apt-get install -y libvorbis-dev")
    message("      sudo apt-get install -y libflac-dev")
    message("      sudo apt-get install -y libx11-dev")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message("Building on Mac")
endif()
message("======================")
