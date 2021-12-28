/**
 *  @file   ClearScreen.hpp
 *  @brief  ClearScreen class interface
 *  @author David
 *  @date   2021-12-14
 ***********************************************/
#ifndef CLEARSCREEN_HPP
#define CLEARSCREEN_HPP

// Include standard library C++ libraries.
#include <string>
// Project header files
#include "Command.hpp"
#include "App.hpp"
using namespace std;

// Represents the command to color a single pixel
class ClearScreen : public Command {
private:
    sf::Image *m_image{};

    static string
    generateCommandDescription(sf::Color prevColor, sf::Color newColor);

public:
    // Construct ClearScreen from App values
    explicit ClearScreen(App *app);

    // Construct ClearScreen with selected color as the new color
    ClearScreen(sf::Image *image, sf::Color prevColor, sf::Color newColor);

    ~ClearScreen() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;

    bool undo() override;

    // These are safe to expose without a getter/setter because they are constant
    const sf::Color m_prevColor;
    const sf::Color m_newColor;
};

#endif
