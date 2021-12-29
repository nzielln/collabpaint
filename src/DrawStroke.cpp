/** 
 *  @file   DrawStroke.cpp 
 *  @brief  DrawStroke implementation, all drawing actions are commands. 
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/

// Include our Third-Party SFML header
// Include standard library C++ libraries.
#include <sstream>
#include <iostream>
#include <cmath>
// Project header files
#include "DrawStroke.hpp"
#include "Draw.hpp"
using namespace std;

//Constructor
DrawStroke::DrawStroke() : Command("Draw in a continual line"), CompositeCommand("Draw in a continual line") {}

/*! \brief 	Compares two commands to see if they're equal
*
*/
bool DrawStroke::operator==(Command &cmd) const {
    // Check if given Command is also a DrawStroke
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    // Dynamic cast to get the other DrawStroke's collection of Draws
    DrawStroke *other = dynamic_cast<DrawStroke *>(&cmd);
    deque<Draw> otherDraws = other->getDraws();

    if (m_draws.size() != otherDraws.size()) {
        return false;
    }

    bool isEqual = true;
    auto thisDraw = m_draws.cbegin();
    auto otherDraw = otherDraws.cbegin();
    while (thisDraw != m_draws.cend() && otherDraw != otherDraws.cend()) {
        isEqual = isEqual && thisDraw == otherDraw;
        thisDraw++;
        otherDraw++;
    }

    return isEqual;
}

/*! \brief Executes a drawstroke command
*		
*/
bool DrawStroke::execute() {
    for (Draw draw: m_draws) {
        draw.execute();
    }

    return true;
}

/*! \brief 	Undoes a drawstroke command
*		
*/
bool DrawStroke::undo() {
    for (Draw draw: m_draws) {
        draw.undo();
    }

    return true;
}


/*! \brief 	Returns all draw commands in drawstroke command
*
*/
deque<Draw> DrawStroke::getDraws() {
    return deque(m_draws);
}

/*! \brief 	Executes a drawstroke command
*
*/
void DrawStroke::addAndExecuteDraw(Draw newDraw) {
    if (!m_draws.empty()) {
        Draw previousDraw = m_draws.back();
        if (newDraw == previousDraw) {
            return;
        }
    }

    m_draws.push_back(newDraw);
    newDraw.execute();
}

/*! \brief 	And and executes a new draw command
*
*/
[[maybe_unused]] void DrawStroke::addAndExecuteCommand(Command *command) {
    Draw *newDraw = dynamic_cast<Draw *>(command);

    if (newDraw) {
        interpolate(*newDraw);
        addAndExecuteDraw(*newDraw);
    } else {
        cerr << "Attempted to add non-draw command to a DrawStroke" << endl;
    }
}

void DrawStroke::interpolate(Draw newestDraw) {
    if (m_draws.size() < 2) {
        return;
    }

    Draw previousDraw = m_draws.back();
    unsigned int x1 = previousDraw.m_posX;
    unsigned int x2 = newestDraw.m_posX;
    unsigned int y1 = previousDraw.m_posY;
    unsigned int y2 = newestDraw.m_posY;

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

        Draw interDraw = Draw(newestDraw.getImage(), newX, newY, newestDraw.m_newColor);

        addAndExecuteDraw(interDraw);
    }
}

DrawStroke::~DrawStroke() = default;
