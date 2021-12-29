/**
 *  @file   Draw.cpp
 *  @brief  Draw implementation, all drawing actions are commands.
 *  @author Mike and Skye
 *  @date   2021-11-12
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
#include <sstream>
#include <iostream>
// Project header files
#include "Draw.hpp"
#include "App.hpp"
using namespace std;

// Constructors
Draw::Draw(App *app) : Draw(
        &app->getImage(),
        app->mouseX,
        app->mouseY,
        app->selectedColor) {}

Draw::Draw(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color newColor) :
        Draw(image, posX, posY, image->getPixel(posX, posY), newColor) {}

Draw::Draw(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor) :
        Command(generateCommandDescription(posX, posY, prevColor, newColor)),
        m_image(image), m_posX(posX), m_posY(posY), m_prevColor(prevColor), m_newColor(newColor) {}

/*! \brief 	Helper function for building a command description string using the Draw's member variables
*
*/
string Draw::generateCommandDescription(
        unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor) {
    stringstream ss;
    ss << "Color pixel (x=" << to_string(posX)
       << ", y=" << to_string(posY)
       << ") from (r=" << to_string(prevColor.r) << ", g=" << to_string(prevColor.g) << ", b="
       << to_string(prevColor.b)
       << ") to (r=" << to_string(newColor.r) << ", g=" << to_string(newColor.g) << ", b="
       << to_string(newColor.b) << ")";
    return ss.str();
}

/*! \brief 	Compares two draw commands to see if they're equal
*
*/
bool Draw::operator==(Command &cmd) const {
    // Check if given Command is also a Draw
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    Draw *other = dynamic_cast<Draw *>(&cmd);

    return this->m_posX == other->m_posX &&
           this->m_posY == other->m_posY &&
           this->m_newColor == other->m_newColor;
}

/*! \brief 	Executes a draw command
*
*/
bool Draw::execute() {
    m_image->setPixel(m_posX, m_posY, m_newColor);

    return true;
}

/*! \brief 	Undoes a draw command
*
*/
bool Draw::undo() {
    m_image->setPixel(m_posX, m_posY, m_prevColor);

    return true;
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image *Draw::getImage() {
    return m_image;
}

/*! \brief 	Draw command destructor
*
*/
Draw::~Draw() = default;
