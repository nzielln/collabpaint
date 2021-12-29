/**
 *  @file   DrawBrush.cpp
 *  @brief  DrawBrush implementation
 *  @author Mark
 *  @date   2021-12-03
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
#include <sstream>
#include <iostream>
#include <cmath>
// Project header files
#include "App.hpp"
#include "DrawBrush.hpp"
using namespace std;

DrawBrush::DrawBrush(App *app) : DrawBrush(
        &app->getImage(),
        app->mouseX,
        app->mouseY,
        app->brushRadius,
        app->selectedColor) {}

DrawBrush::DrawBrush(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor) :
        Command(generateCommandDescription(posX, posY, rad, newColor)),
        m_image(image), m_posX(posX), m_posY(posY), m_radius(rad), //m_prevColors(prevColors),
        m_newColor(newColor) {

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

/*! \brief 	Helper function for building a commmand description string
* using the a Draw's member variables
*
*/
string DrawBrush::generateCommandDescription(
        unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor) {
    stringstream ss;
    ss << "Color pixel (x=" << to_string(posX)
       << ", y=" << to_string(posY)
       << ") to (r=" << to_string(newColor.r) << ", g=" << to_string(newColor.g) << ", b="
       << to_string(newColor.b) << ")"
       << "with radius " << to_string(rad);
    return ss.str();
}

bool DrawBrush::operator==(Command &cmd) const {
    // Check if given Command is also a DrawBrush
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    DrawBrush *other = dynamic_cast<DrawBrush *>(&cmd);

    return
            this->m_posX == other->m_posX &&
            this->m_posY == other->m_posY &&
            this->m_radius == other->m_radius &&
            this->m_newColor == other->m_newColor;
}

/*! \brief 	N/A
*
*/
bool DrawBrush::execute() {
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
bool DrawBrush::undo() {

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

sf::Image *DrawBrush::getImage() {
    return m_image;
}

DrawBrush::~DrawBrush() = default;
