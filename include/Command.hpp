/** 
 *  @file   Command.hpp 
 *  @brief  Represents an actionable command by the user.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include standard library C++ libraries.
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Network.hpp>
using namespace std;

// The command class
class Command {
public:
    //Constructor
    explicit Command(string commandDescription);

    //Destructor
    virtual ~Command();

    // Commands must overload equality
    // If performing the 2 commands back to back would produce no visual changes, we consider them "equal"
    virtual bool operator==(Command &other) const = 0;

    // Returns true or false if the command was able to successfully execute.
    virtual bool execute() = 0;

    // Executes the command "in reverse", undoing the behavior
    virtual bool undo() = 0;

    // Description of the command for debugging purposes
    [[maybe_unused]] const string m_commandDescription;
};

#endif
