/**
 *  @file   EraserStroke.cpp
 *  @brief  EraserStroke implementation, all erasing actions are commands.
 *  @author Mike, Skye and Ellah
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
#include "EraserStroke.hpp"
#include "Eraser.hpp"
using namespace std;

//Constructor
EraserStroke::EraserStroke() : Command("Erase in a continual line"), CompositeCommand("Erase in a continual line") {}

/*! \brief 	Compares two commands to see if they're equal
*
*/
bool EraserStroke::operator==(Command &cmd) const {
    // Check if given Command is also a EraserStroke
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    // Dynamic cast to get the other EraserStroke's collection of Draws
    EraserStroke *other = dynamic_cast<EraserStroke *>(&cmd);
    deque<Eraser> otherErasers = other->getErasers();

    if (m_eraser.size() != otherErasers.size()) {
        return false;
    }

    bool isEqual = true;
    auto thisEraser = m_eraser.cbegin();
    auto otherEraser = otherErasers.cbegin();
    while (thisEraser != m_eraser.cend() && otherEraser != otherErasers.cend()) {
        isEqual = isEqual && thisEraser == otherEraser;
        thisEraser++;
        otherEraser++;
    }

    return isEqual;
}

/*! \brief 	Executes a new eraser command
*
*/
bool EraserStroke::execute() {
    for (Eraser eraser: m_eraser) {
        eraser.execute();
    }

    return true;
}

/*! \brief 	Undoes an eraserstroke command
*
*/
bool EraserStroke::undo() {
    for (Eraser eraser: m_eraser) {
        eraser.undo();
    }

    return true;
}

/*! \brief 	Returns all eraser commands in eraserstroke
*
*/
deque<Eraser> EraserStroke::getErasers() {
    return deque(m_eraser);
}

void EraserStroke::addAndExecuteDraw(Eraser newEraser) {
    if (!m_eraser.empty()) {
        Eraser previousEraser = m_eraser.back();
        if (newEraser == previousEraser) {
            return;
        }
    }

    m_eraser.push_back(newEraser);
    newEraser.execute();
}


/*! \brief 	And and executes a new eraser command
*
*/
[[maybe_unused]] void EraserStroke::addAndExecuteCommand(Command *command) {
    Eraser *newEraser = dynamic_cast<Eraser *>(command);

    if (newEraser) {
        interpolate(*newEraser);
        addAndExecuteDraw(*newEraser);
    } else {
        cerr << "Attempted to add non-draw command to a EraserStroke" << endl;
    }
}

void EraserStroke::interpolate(Eraser newestEraser) {
    if (m_eraser.size() < 2) {
        return;
    }

    Eraser previousEraser = m_eraser.back();
    unsigned int x1 = previousEraser.m_posX;
    unsigned int x2 = newestEraser.m_posX;
    unsigned int y1 = previousEraser.m_posY;
    unsigned int y2 = newestEraser.m_posY;

    int distX = static_cast<int>(x1 - x2);
    int distY = static_cast<int>(y1 - y2);
    double distance = sqrt(pow(distX, 2) + pow(distY, 2) * 1.0);

    for (int i = 1; i <= distance; i++) {
        int newX = distX == 0 ?
                   static_cast<int>(x1) :
                   static_cast<int>(x1 - round(i * distX / distance));
        int newY = distY == 0 ?
                   static_cast<int>(y1) :
                   static_cast<int>(y1 - round(i * distY / distance));

        Eraser interEraser = Eraser(newestEraser.getImage(), newX, newY, newestEraser.m_radius, newestEraser.m_newColor);

        addAndExecuteDraw(interEraser);
    }
}

/*! \brief 	Destructor
*
*/
EraserStroke::~EraserStroke() = default;