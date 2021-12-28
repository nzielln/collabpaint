/**
 *  @file   Eraser.cpp
 *  @brief  Eraser implementation, all drawing actions are commands.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
#include <sstream>
#include <iostream>
// Project header files
#include "App.hpp"
#include "Eraser.hpp"

Eraser::Eraser(App *app) : Eraser(
        &app->getImage(),
        app->mouseX,
        app->mouseY,
        app->backgroundColor) {}

Eraser::Eraser(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color newColor) :
        Eraser(image, posX, posY, image->getPixel(posX, posY), newColor) {}

Eraser::Eraser(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor) :
        Command(generateCommandDescription(posX, posY, prevColor, newColor)),
        m_image(image), m_posX(posX), m_posY(posY), m_prevColor(prevColor), m_newColor(newColor) {}

/*! \brief 	Helper function for building a command description string
* using the a Draw's member variables
*
*/
std::string Eraser::generateCommandDescription(
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

bool Eraser::operator==(Command &cmd) const {
    // Check if given Command is also a Draw
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    Eraser *other = dynamic_cast<Eraser *>(&cmd);

    return
            this->m_posX == other->m_posX &&
            this->m_posY == other->m_posY &&
            this->m_newColor == other->m_newColor;
}

/*! \brief 	N/A
*
*/
bool Eraser::execute() {
    m_image->setPixel(m_posX, m_posY, m_newColor);

    return true;
}

/*! \brief 	N/A
*
*/
bool Eraser::undo() {
    m_image->setPixel(m_posX, m_posY, m_prevColor);

    return true;
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image *Eraser::getImage() {
    return m_image;
}

Eraser::~Eraser() = default;