/** 
 *  @file   DrawStroke.hpp 
 *  @brief  Interface for drawing a continuous line
 *  @author Skye
 *  @date   2021-29-11
 ***********************************************/
#ifndef DRAWSTROKE_H
#define DRAWSTROKE_H

// Include standard library C++ libraries.
#include <string>
// Project header files
#include "CompositeCommand.hpp"
#include "Draw.hpp"
using namespace std;

// Represents the command to color a series of pixels from mouse-down to mouse-up
class DrawStroke : public CompositeCommand {
private:
    deque<Draw> m_draws;

    // Generate and add new draws for pixels between the two most recently added draws
    void interpolate(Draw newestDraw);

    // Add a draw to m_draws if it is unique and execute it
    void addAndExecuteDraw(Draw newDraw);

public:
    //Constructor
    explicit DrawStroke();

    //Destructor
    ~DrawStroke() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;
    bool undo() override;
    [[maybe_unused]] void addAndExecuteCommand(Command *c) override;

    // Returns a copy of the draws currently in this DrawStroke
    deque<Draw> getDraws();
};

#endif
