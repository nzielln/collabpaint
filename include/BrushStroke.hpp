/**
 *  @file   BrushStroke.hpp
 *  @brief  BrushStroke class interface
 *  @author Mark
 *  @date   2021-12-14
 ***********************************************/
#ifndef BRUSHSTROKE_H
#define BRUSHSTROKE_H

// Include standard library C++ libraries.
#include <string>
// Project header files
#include "CompositeCommand.hpp"
#include "DrawBrush.hpp"
#include "App.hpp"
using namespace std;

// Represents the command to color a series of pixels from mouse-down to mouse-up
class BrushStroke : public CompositeCommand {
private:
    deque<DrawBrush> m_draws;

    // Generate and add new DrawBrushes to connect the two most recently added DrawBrushes
    void interpolate(DrawBrush newestDraw);

    // Add a DrawBrush to m_draws if it is unique and execute it
    void addAndExecuteDraw(DrawBrush newDraw);

public:
    explicit BrushStroke();

    ~BrushStroke() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;

    bool undo() override;

    void addAndExecuteCommand(Command *c) override;

    // Returns a copy of the DrawBrushes currently in this BrushStroke
    deque<DrawBrush> getDraws();
};

#endif