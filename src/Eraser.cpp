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
#include <cmath>
// Project header files
#include "App.hpp"
#include "Eraser.hpp"
using namespace std;

Eraser::Eraser(App *app) : Eraser(
        &app->getImage(),
        app->mouseX,
        app->mouseY,
        app->brushRadius,
        app->backgroundColor) {}

Eraser::Eraser(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor) :
        Command(generateCommandDescription_b(posX, posY, rad, newColor)), m_image(image), m_posX(posX), m_posY(posY),
        m_radius(rad), m_newColor(newColor) {
    unsigned int minX = m_posX - m_radius;
    unsigned int minY = m_posY - m_radius;

    m_prevColors.resize(2 * rad, vector<sf::Color>(2 * rad));

    for (unsigned int i = 0; i < 2 * rad; i++) {
        for (unsigned int j = 0; j < 2 * rad; j++) {
            if (sqrt((i - m_radius) * (i - m_radius) + (j - m_radius) * (j - m_radius)) <= m_radius
                && minX + i >= 0 && minX + i < App::WINDOW_WIDTH && minY + j >= 0 && minY + j < App::WINDOW_HEIGHT) {
                m_prevColors[i][j] = m_image->getPixel(minX + i, minY + j);
            }
        }
    }
}

Eraser::Eraser(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color prevColor, sf::Color newColor) :
        Command(generateCommandDescription_a(posX, posY, rad, prevColor, newColor)),
        m_image(image), m_posX(posX), m_posY(posY), m_radius(rad), //m_prevColor(prevColor),
        m_newColor(newColor) {

}

/*! \brief 	Helper function for building a command description string
* using the a Draw's member variables
*
*/
string Eraser::generateCommandDescription_a(
        unsigned int posX, unsigned int posY, unsigned int rad, sf::Color prevColor, sf::Color newColor) {
    stringstream ss;
    ss << "Color pixel (x=" << to_string(posX)
       << ", y=" << to_string(posY)
       << ") from (r=" << to_string(prevColor.r) << ", g=" << to_string(prevColor.g) << ", b="
       << to_string(prevColor.b)
       << ") to (r=" << to_string(newColor.r) << ", g=" << to_string(newColor.g) << ", b="
       << to_string(newColor.b) << ")"
       << "with radius " << to_string(rad);
    return ss.str();
}

/*! \brief 	Helper function for building a command description string
* using the a Draw's member variables
*
*/
string Eraser::generateCommandDescription_b(
        unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor) {
    stringstream ss;
    ss << "Color pixel (x=" << to_string(posX)
       << ", y=" << to_string(posY)
       << ") to (r=" << to_string(newColor.r) << ", g=" << to_string(newColor.g) << ", b="
       << to_string(newColor.b) << ")"
       << "with radius " << to_string(rad);
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
            this->m_radius == other->m_radius &&
            this->m_newColor == other->m_newColor;
}

/*! \brief 	N/A
*
*/
bool Eraser::execute() {
    //m_image->setPixel(m_posX, m_posY, m_newColor);
    unsigned int minX = m_posX - m_radius;
    unsigned int minY = m_posY - m_radius;
    unsigned int size = m_radius + m_radius;

    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            if (sqrt((i - m_radius) * (i - m_radius) + (j - m_radius) * (j - m_radius)) <= m_radius
                && minX + i >= 0 && minX + i < App::WINDOW_WIDTH && minY + j >= 0 && minY + j < App::WINDOW_HEIGHT) {
                m_image->setPixel(minX + i, minY + j, m_newColor);
            }
        }
    }


    return true;
}

/*! \brief 	N/A
*
*/
bool Eraser::undo() {
    //m_image->setPixel(m_posX, m_posY, m_prevColor);
    unsigned int minX = m_posX - m_radius;
    unsigned int minY = m_posY - m_radius;
    unsigned int size = 2 * m_radius;

    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            if (sqrt((i - m_radius) * (i - m_radius) + (j - m_radius) * (j - m_radius)) <= m_radius) {
                m_image->setPixel(minX + i, minY + j, m_prevColors[i][j]);
            }
        }
    }

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