/**
 *  @file   EraserStroke.hpp
 *  @brief  EraserStroke actions interface.
 *  @author Skye
 *  @date   2021-29-11
 ***********************************************/
#ifndef ERASERSTROKE_H
#define ERASERSTROKE_H

// Include standard library C++ libraries.
#include <string>
// Project header files
#include "CompositeCommand.hpp"
#include "Eraser.hpp"
using namespace std;

// Represents the command to color a series of pixels from mouse-down to mouse-up
class EraserStroke : public CompositeCommand {
private:
    deque<Eraser> m_eraser;

    // Generate and add new draws for pixels between the two most recently added draws
    void interpolate(Eraser newestEraser);

    // Add a draw to m_draws if it is unique and execute it
    void addAndExecuteDraw(Eraser newEraser);

public:
    //Constructor
    explicit EraserStroke();

    //Destructor
    ~EraserStroke() override;

    bool operator==(Command &cmd) const override;

    bool execute() override;
    bool undo() override;
    [[maybe_unused]] void addAndExecuteCommand(Command *c) override;

    // Returns a copy of the draws currently in this EraserStroke
    deque<Eraser> getErasers();
};

#endif