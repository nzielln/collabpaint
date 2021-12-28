/**
 *  @file   CompositeCommand.hpp
 *  @brief  Represents a command which is comprised of other commands.
 *  @author Skye
 *  @date   2021-12-14
 ***********************************************/
#ifndef COMPOSITECOMMAND_HPP
#define COMPOSITECOMMAND_HPP

// Include standard library C++ libraries.
#include <string>
#include <deque>
#include "Command.hpp"
using namespace std;

// The command class
class CompositeCommand : public virtual Command {
public:
    explicit CompositeCommand(string commandDescription);

    // Adds a new command to the collection
    virtual void addAndExecuteCommand(Command *c) = 0;
};

#endif

