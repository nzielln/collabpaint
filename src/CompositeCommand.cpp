/**
 *  @file   CompositeCommand.cpp
 *  @brief  Implementation of CompositeCommand.hpp
 *  @author Skye
 *  @date   2021-11-30
 ***********************************************/

// Include standard library C++ libraries.
#include <utility>
// Project header files
#include "CompositeCommand.hpp"

/*! \brief 	N/A
*		
*/
CompositeCommand::CompositeCommand(std::string commandDescription) : Command(std::move(commandDescription)) {}
