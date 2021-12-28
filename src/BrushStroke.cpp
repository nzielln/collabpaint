/**
 *  @file   DrawStroke.cpp
 *  @brief  DrawStroke implementation, all drawing actions are commands.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/

// Include standard library C++ libraries.
#include <sstream>
#include <iostream>
#include <cmath>
// Project header files
#include "App.hpp"
#include "BrushStroke.hpp"
#include "DrawBrush.hpp"

BrushStroke::BrushStroke() : Command("Draw with brush in a continual line"),
                             CompositeCommand("Draw with brush in a continual line") {}

bool BrushStroke::operator==(Command &cmd) const {
    // Check if given Command is also a BrushStroke
    if (typeid(this) != typeid(cmd)) {
        return false;
    }

    // Dynamic cast to get the other BrushStroke's collection of DrawBrushes
    BrushStroke *other = dynamic_cast<BrushStroke *>(&cmd);
    std::deque<DrawBrush> otherDraws = other->getDraws();

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

/*! \brief 	N/A
*
*/
bool BrushStroke::execute() {
    for (DrawBrush draw: m_draws) {
        draw.execute();
    }

    return true;
}

/*! \brief 	N/A
*
*/
bool BrushStroke::undo() {
//    for (DrawBrush draw: m_draws) {
//        draw.undo();
//    }
    std::stack<DrawBrush> drawStack;

    for (DrawBrush draw: m_draws) {
        drawStack.push(draw);
    }

    while (!drawStack.empty()) {
        drawStack.top().undo();
        drawStack.pop();
    }

    return true;
}

std::deque<DrawBrush> BrushStroke::getDraws() {
    return std::deque(m_draws);
}

void BrushStroke::addAndExecuteDraw(DrawBrush newDraw) {
    if (!m_draws.empty()) {
        DrawBrush previousDraw = m_draws.back();
        if (newDraw == previousDraw) {
            return;
        }
    }

    m_draws.push_back(newDraw);
    newDraw.execute();
}

[[maybe_unused]] void BrushStroke::addAndExecuteCommand(Command *command) {
    DrawBrush *newDraw = dynamic_cast<DrawBrush *>(command);

    if (newDraw) {
        interpolate(*newDraw);
        addAndExecuteDraw(*newDraw);
    } else {
        std::cerr << "Attempted to add non-draw command to a BrushStroke" << std::endl;
    }
}

void BrushStroke::interpolate(DrawBrush newestDraw) {
    if (m_draws.size() < 2) {
        return;
    }

    DrawBrush previousDraw = m_draws.back();
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

        DrawBrush interDraw = DrawBrush(newestDraw.getImage(), newX, newY, newestDraw.m_radius, newestDraw.m_newColor);

        addAndExecuteDraw(interDraw);
    }
}

BrushStroke::~BrushStroke() = default;