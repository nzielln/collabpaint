/**
 *  @file   Draw.hpp
 *  @brief  Drawing actions interface.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include standard library C++ libraries.
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Network.hpp>
// Project header files
#include "Command.hpp"
#include "App.hpp"

// Represents the command to color a single pixel
class Draw : public Command {
private:
    sf::Image *m_image{};

    static std::string
    generateCommandDescription(unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor);

public:
    // Redid this to avoid circular dependency between Draw and App
    // Refactored app so everything still works fine
    // Construct Draw from App values
    explicit Draw(App *app);

    // Grab prevColor from image
    Draw(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color newColor);

    // Default constructor
    Draw(sf::Image *image, unsigned int posX, unsigned int posY, sf::Color prevColor, sf::Color newColor);

    ~Draw() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;

    bool undo() override;

    sf::Image *getImage();

    // These are safe to expose without a getter/setter because they are constant
    const unsigned int m_posX;
    const unsigned int m_posY;
    const sf::Color m_prevColor;
    const sf::Color m_newColor;
};

#endif
