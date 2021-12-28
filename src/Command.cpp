/** 
 *  @file   Command.cpp 
 *  @brief  Implementation of Command.hpp
 *  @author Mike and Skye
 *  @date   2021-11-12
 ***********************************************/

// Include standard library C++ libraries.
#include <utility>
// Project header files
#include "Command.hpp"
using namespace std;

/*! \brief 	N/A
*		
*/
Command::Command(string commandDescription) : m_commandDescription(move(commandDescription)) {}

/*! \brief 	N/A
*		
*/
Command::~Command() = default;
