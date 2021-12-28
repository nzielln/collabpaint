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

// See comment in Draw.hpp
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
std::string Draw::generateCommandDescription(
        unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor) {
    std::stringstream ss;
    ss << "Color pixel (x=" << std::to_string(posX)
       << ", y=" << std::to_string(posY)
       << ") from (r=" << std::to_string(prevColor.r) << ", g=" << std::to_string(prevColor.g) << ", b="
       << std::to_string(prevColor.b)
       << ") to (r=" << std::to_string(newColor.r) << ", g=" << std::to_string(newColor.g) << ", b="
       << std::to_string(newColor.b) << ")";
    return ss.str();
}

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

/*! \brief 	N/A
*
*/
bool Draw::execute() {
    m_image->setPixel(m_posX, m_posY, m_newColor);

    return true;
}

/*! \brief 	N/A
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

Draw::~Draw() = default;
