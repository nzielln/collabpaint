/**
 *  @file   DrawBrush.hpp
 *  @brief  Interface for drawing with a dynamic radius
 *  @author Mark
 *  @date   2021-12-14
 ***********************************************/
#ifndef DRAWBRUSH_H
#define DRAWBRUSH_H

// Include standard library C++ libraries.
#include <string>
#include <vector>
// Project header files
#include "Command.hpp"
using namespace std;

class DrawBrush : public Command {
private:
    sf::Image *m_image{};

    static string
    generateCommandDescription(unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor);

public:
    // Construct DrawBrush from App values
    DrawBrush(App *app);

    // Construct DrawBrush with given new color and radius
    DrawBrush(sf::Image *image, unsigned int posX, unsigned int posY, unsigned int rad, sf::Color newColor);

    //Destructor
    ~DrawBrush() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;
    bool undo() override;

    sf::Image *getImage();

    // These are safe to expose without a getter/setter because they are constant
    const unsigned int m_posX;
    const unsigned int m_posY;
    const unsigned int m_radius;
    vector<vector<sf::Color>> m_prevColors;
    const sf::Color m_newColor;
};

#endif
