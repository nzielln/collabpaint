## CS5500 Final Project - Collaborative Paint
Final project for CS5500 (Foundation to Software Engineering), a collaborative paint app that uses networking and allows multiple people to draw on a shared canvas from different addresses.

# Tools and Libraries
- SFML - Main Framework
- Nuklear - GUI
- CMake - Build
- Catch2 - Testing

# Language
- C++

# Main Role
Implementing the networking aspect of the project

# Build Instructions:
*Note: these instructions are intended for a Mac OS users. The program should function across operating systems, but may require some manual work to install SFML/OpenGL dependencies in those cases.*

1. Run `cmake ..` to generate a MakeFile
2. Run `make` to build the software. 
   1. On Mac, this should automatically fetch required dependency libraries. If there are problems retrieving these dependencies, you can manually add the following content to `/bin/_deps`
      1. `glad-build`, `glad-src`, `glad-subbuild`, `glfw-build`, `glfw-src`, `glfw-subbuild`, `sfml-build`, `sfml-src`, `sfml-subbuild`
3. Start the App with `./App`
4. Start Server:
   1. When prompted, enter `s` to start the server
   2. When prompted, enter an unused port to run the Application on (ex: 50001)
   3. Assuming all goes well, you should see the message `Starting TCP Network server`
5. Join as a client:
    1. When prompted, enter `c` to join the server as a client
    2. When prompted, enter a unique username for the server
    3. When prompted, enter the same port as used for the server
    4. 3. Assuming all goes well, you should see the message `Connection Request sent`, and see a GUI window and a Drawing window open
7. You're all set! You should be able to draw across canvases, erase, clear the screen, undo and redo, and use the GUI to customize your brush size and color.


