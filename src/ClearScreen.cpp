/**
 *  @file   ClearScreen.cpp
 *  @brief  Clear Screen implementation, all drawing actions are commands.
 *  @author David
 *  @date   2021-12-14
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
#include <sstream>
// Project header files
#include "App.hpp"
#include "ClearScreen.hpp"

ClearScreen::ClearScreen(App *app) : ClearScreen(
        &app->getImage(),
        app->getBGColor(),
        app->selectedColor) {}

ClearScreen::ClearScreen(sf::Image *image, sf::Color prevColor, sf::Color newColor) :
        Command(generateCommandDescription(prevColor, newColor)),
        m_image(image), m_prevColor(prevColor), m_newColor(newColor) {}

/*! \brief 	Helper function for building a command description string using the ClearScreen's member variables
*
*/
std::string ClearScreen::generateCommandDescription(sf::Color prevColor, sf::Color newColor) {
    std::stringstream ss;
    ss << "Previous screen color was: " << std::to_string(prevColor.g)
       << "Clearing new screen color to: " << std::to_string(newColor.g);
    return ss.str();
}

bool ClearScreen::operator==(Command &cmd) const {
    // Check if given Command is also a ClearScreen
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    ClearScreen *other = dynamic_cast<ClearScreen *>(&cmd);

    return this->m_newColor == other->m_newColor;
}

/*! \brief 	N/A
*
*/
bool ClearScreen::execute() {
    m_image->create(App::WINDOW_WIDTH, App::WINDOW_HEIGHT, m_newColor);

    return true;
}

/*! \brief 	N/A
*
*/
bool ClearScreen::undo() {
    m_image->create(App::WINDOW_WIDTH, App::WINDOW_HEIGHT, m_prevColor);

    return true;
}

ClearScreen::~ClearScreen() = default;
