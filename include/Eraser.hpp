/**
 *  @file   Eraser.hpp
 *  @brief  Erasing actions interface.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/
#ifndef ERASER_H
#define ERASER_H

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
using namespace std;

// Represents the command to color a single pixel
class Eraser : public Command {
private:
    sf::Image *m_image{};

    static string generateCommandDescription_a(unsigned int posX, unsigned int posY, unsigned int rad,
                                               sf::Color prevColor, sf::Color newColor);
    static string generateCommandDescription_b(unsigned int posX, unsigned int posY, unsigned int rad,
                                               sf::Color newColor);


public:
    // Construct Eraser from App values
    explicit Eraser(App *app);

    // Grab prevColor from image
    Eraser(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor);

    // Default constructor
    Eraser(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color prevColor,
           sf::Color newColor);

    ~Eraser() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;
    bool undo() override;

    sf::Image *getImage();

    // These are safe to expose without a getter/setter because they are constant
    const unsigned int m_posX;
    const unsigned int m_posY;
    const unsigned int m_radius;
    vector<vector<sf::Color>> m_prevColors;
    sf::Color m_newColor;
};

#endif