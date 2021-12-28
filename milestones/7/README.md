# Building Software

- [ ] Instructions on how to build your software should be written in this file
	- This is especially important if you have added additional dependencies.
	- Assume someone who has not taken this class (i.e. you on the first day) would have read, build, and run your software from scratch.
- You should have at a minimum in your project
	- [ ] A CMakeLists.txt in a root directory
    	- [ ] This should generate a 'release' version of your software
  - [ ] Run your code with the latest version of cppcheck before commiting your code (could be a github action)
  - [ ] (Optional) Run your code with the latest version of clang-tidy  (could be a github action)

*Modify this file to include instructions on how to build and run your software. Specify which platform you are running on. Running your software involves launching a server and connecting at least 2 clients to the server.*

# Build Instructions:
Note, these instructions are intended for a Mac user. The program should function across operating systems, but may require some manual work to install SFML/OpenGL dependencies in those cases.

1. Open the terminal, and in 3 separate windows / tabs navigate to the finalproject-team-16/FinalProject/bin directory
2. Run `cmake ..` to generate a MakeFile
3. Run `make` to build the software. 
   1. On Mac, this should automatically fetch required dependency libraries. If there are problems retrieving these dependencies, you can manually add the following content to `/bin/_deps`
      1. `glad-build`, `glad-src`, `glad-subbuild`, `glfw-build`, `glfw-src`, `glfw-subbuild`, `sfml-build`, `sfml-src`, `sfml-subbuild`
4. In the first window, start the App with `./App`
   1. When prompted, enter `s` to start the server
   2. When prompted, enter an unused port to run the Application on (ex: 50001)
   3. Assuming all goes well, you should see the message `Starting TCP Network server`
5. Switch to the second window, and start the App with `./App`
    1. When prompted, enter `c` to join the server as a client
    2. When prompted, enter a unique username for the server
    3. When prompted, enter the same port as used in step 4ii
    4. 3. Assuming all goes well, you should see the message `Connection Request sent`, and see a GUI window and a Drawing window open
6. Switch to the third window, and repeat step 5 to join as a second client
7. You're all set! You should be able to draw across canvases, erase, clear the screen, undo and redo, and use the GUI to customize your brush size and color.