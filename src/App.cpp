/**
 *  @file   App.cpp
 *  @brief  Main class for program
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/

// Include some standard libraries
// The 'C-based' libraries are needed for Nuklear GUI


// NUKLEAR - for our GUI
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION

#include <stdarg.h>
#include <string.h>
#include <OpenGL/gl.h>
#include "nuklear.h"
#include "nuklear_sfml_gl2.h"


// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>

// Include standard library C++ libraries.
#include <cassert>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <ClearScreen.hpp>

// Project header files
#include "App.hpp"
#include "CompositeCommand.hpp"
#include "DrawStroke.hpp"

using namespace std;

struct nk_colorf bg;
struct nk_context *ctx;

const vector<Mode> App::PRESET_MODES = { // NOLINT(cert-err58-cpp)
        {
                .label = "Draw",
                .mode = DRAW_MODE
        },
        {
                .label = "Erase",
                .mode = ERASE_MODE
        }
};
const vector<PresetColor> App::PRESET_COLORS = { // NOLINT(cert-err58-cpp,cppcoreguidelines-interfaces-global-init)
        {
                .label = "Black",
                .color = sf::Color::Black
        },
        {
                .label = "White",
                .color = sf::Color::White
        },
        {
                .label = "Red",
                .color = sf::Color::Red
        },
        {
                .label = "Green",
                .color = sf::Color::Green
        },
        {
                .label = "Blue",
                .color = sf::Color::Blue
        },
        {
                .label = "Yellow",
                .color = sf::Color::Yellow
        },
        {
                .label = "Magenta",
                .color = sf::Color::Magenta
        },
        {
                .label = "Cyan",
                .color = sf::Color::Cyan
        }
};

App::App(void (*updateFunction)(App *), void (*drawFunction)(App *)) {
    m_updateFunc = updateFunction;
    m_drawFunc = drawFunction;
    selectedColor = sf::Color::Black;
    backgroundColor = sf::Color::White;
    selectedMode = DRAW_MODE;

    mouseX = 0;
    mouseY = 0;
    brushRadius = 1;

    m_window = nullptr;
    m_image = new sf::Image;
    m_sprite = new sf::Sprite;
    m_texture = new sf::Texture;
    m_clock = new sf::Clock;

    // Setup the context
    sf::ContextSettings settings(24, 8, 4, 2, 2);
    // Create our window
    m_window = new sf::RenderWindow(sf::VideoMode(App::WINDOW_WIDTH, App::WINDOW_HEIGHT), "Mini-Paint alpha 0.0.2",
                                    sf::Style::Titlebar);
    m_window->setVerticalSyncEnabled(true);

    // Create an image which stores the pixels we will update
    m_image->create(App::WINDOW_WIDTH, App::WINDOW_HEIGHT, sf::Color::White);
    assert(m_image != nullptr && "m_image != nullptr");

    // Create a texture which lives in the GPU and will render our image
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");

    // Create a sprite which is the entity that can be textured
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");

    // Create a GUI window to draw to
    gui_window = new sf::RenderWindow(
            sf::VideoMode(GUI_WIDTH, WINDOW_HEIGHT),
            "",
            sf::Style::Default, settings
    );
    gui_window->setVerticalSyncEnabled(true);
    gui_window->setActive(true);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    glViewport(0, 0,
               gui_window->getSize().x,  // NOLINT(cppcoreguidelines-narrowing-conversions)
               gui_window->getSize().y); // NOLINT(cppcoreguidelines-narrowing-conversions)
#pragma clang diagnostic pop
    ctx = nk_sfml_init(gui_window);
    // Load Fonts: if none of these are loaded a default font will be used
    // Load Cursor: if you uncomment cursor loading please hide the cursor
    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();
    // Setup a color for the nuklear gui
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
}

/*! \brief 	Render our GUI
*
*/
void App::drawLayout() {
    if (nk_begin(ctx, "Settings", nk_rect(0, 0, GUI_WIDTH, WINDOW_HEIGHT),
                 NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {

        // Undo + Redo
        nk_layout_row_static(ctx, 30, 90, 2);
        if (nk_button_label(ctx, "Undo")) {
            undoCommand();
        }
        if (nk_button_label(ctx, "Redo")) {
            redoCommand();
        }

        // Spacer
        nk_layout_row_dynamic(ctx, 20, 1);

        // Color Select
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Color:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 30, 2);
        for (PresetColor color: PRESET_COLORS) {
            if (nk_option_label(ctx, color.label, selectedColor == color.color)) {
                selectedColor = color.color;
            }
        }

        // Spacer
        nk_layout_row_dynamic(ctx, 20, 1);

        // Brush Size
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Brush Size:", NK_TEXT_LEFT);
        nk_layout_row_static(ctx, 30, 60, 3);
        if (nk_button_label(ctx, "-")) {
            decrementBrushRadius();
        }
        nk_label(ctx, to_string(brushRadius).c_str(), NK_TEXT_CENTERED);
        if (nk_button_label(ctx, "+")) {
            incrementBrushRadius();
        }

        // Spacer
        nk_layout_row_dynamic(ctx, 20, 1);

        // Mode Selector
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Mode:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 30, 2);
        for (Mode mode: PRESET_MODES) {
            if (nk_option_label(ctx, mode.label, selectedMode == mode.mode)) {
                selectedMode = mode.mode;
            }
        }

        // Spacer
        nk_layout_row_dynamic(ctx, 20, 1);

        // Clear Screen
        nk_layout_row_static(ctx, 30, 190, 1);
        if (nk_button_label(ctx, "Clear Screen")) {
            addCommand(new ClearScreen(this));
        }
    }
    nk_end(ctx);
}

/*! \brief 	Add a new command to the queue,
* execute it, and clear undo history.
*
*/
void App::addCommand(Command *c) {
    executeCommand(c);
    // clear undo history
    while (!m_undo.empty()) {
        delete m_undo.top();
        m_undo.pop();
    }
}

/*! \brief Add the given CompositeCommand to inProgressCommands associated with the given username
*
*/
void App::startComposite(const string &username, CompositeCommand *c) {
    m_inProgressCommands.emplace(pair<string, CompositeCommand *>(username, c));
}

/*! \brief End and destroy the CompositeCommand associated with the given username
*
*/
void App::endComposite(const string &username) {
    vector<CompositeCommand *> todel;
    map<string, CompositeCommand *>::iterator it;
    for (it = m_inProgressCommands.begin(); it != m_inProgressCommands.end(); ++it) {
        if (it->first == username) {
            todel.push_back(it->second);
            m_inProgressCommands.erase(it->first);
            break;
        }
    }

    for(auto &t : todel) {
        m_commands.push_front(t);
    }
}

/*! \brief 	Add and execute the given Command to the CompositeCommand associated with the given username
*
*/
void App::addToComposite(const string &username, Command *c) {
    try {
        CompositeCommand *composite = m_inProgressCommands.at(username);
        composite->addAndExecuteCommand(c);
        m_commands.push_front(c);
    } catch (out_of_range) {
        cerr << username << " has no CompositeCommand to add to" << endl;
    }
}

/*! \brief 	Helper function for executing a command
* and maintaining the size of the queue
*
*/
void App::executeCommand(Command *c) {
    if (!m_commands.empty()) {
        // If new command is the same as the front of the deque, exit to avoid duplication
        if (c == m_commands.front()) {
            return;
        }

        // Maintain remembered commands size
        if (m_commands.size() == MAX_REMEMBERED_COMMANDS) {
            delete m_commands.back();
            m_commands.pop_back();
            assert(m_commands.size() < MAX_REMEMBERED_COMMANDS && "remembered commands < 100");
        }
    }

    // Maintain remembered commands size
    if (m_commands.size() == App::MAX_REMEMBERED_COMMANDS) {
        delete m_commands.back();
        m_commands.pop_back();
        assert(m_commands.size() < App::MAX_REMEMBERED_COMMANDS && "remembered commands < 100");
    }

    // push & execute
    m_commands.push_front(c);
    c->execute();
}

/*! \brief 	Undo the most recently performed command
*
*/
void App::undoCommand() {
    if (!m_commands.empty()) {
        m_commands.front()->undo();

        m_undo.push(m_commands.front());
        m_commands.pop_front();

    }
}

/*! \brief 	Redo the most recently undone command
*
*/
void App::redoCommand() {
    if (!m_undo.empty()) {
        App::executeCommand(m_undo.top());
        m_undo.pop();
    }
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image &App::getImage() {
    return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*
*/
sf::Texture &App::getTexture() {
    return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*
*/
sf::RenderWindow &App::getWindow() {
    return *m_window;
}

/*! \brief 	Return a reference to our m_clock so that we
*		do not have to publicly expose it.
*
*/
sf::Clock &App::getClock() {
    return *m_clock;
}


/*! \brief Gets the selectedColor of the app
 *
 */
sf::Color App::getBGColor() {
    return backgroundColor;
}

/*! \brief Gets the selectedMode of the app
 *
 */
int App::getMode() {
    return selectedMode;
}


/*! \brief Sets the background color of the app to be the color that the user inputs
 *
 */
void App::setBGColor(sf::Color newBGColor) {
    backgroundColor = newBGColor;
}

/*! \brief Sets the selectedMode of the app to be the mode that the user inputs
 *
 */
void App::setMode(int newMode) {
    selectedMode = newMode;
}

/*! \brief 	destroy we manually call at end of our program.
*
*/
void App::destroy() {
    delete m_image;
    delete m_sprite;
    delete m_texture;
}

void App::handleGUIInput() {
    // Capture events in our main window
    sf::Event event; // NOLINT(cppcoreguidelines-pro-type-member-init)

    // Capture input from the nuklear GUI
    nk_input_begin(ctx);
    while (gui_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                nk_sfml_shutdown();
                gui_window->close();
                exit(EXIT_SUCCESS);
            }
        }
        nk_sfml_handle_event(&event);
    }

    // Complete input from nuklear GUI
    nk_input_end(ctx);
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*
*/
void App::loop() {
    // Start the main rendering loop
    while (m_window->isOpen() && gui_window->isOpen()) {
        drawLayout();
        // OpenGL is the background rendering engine,
        // so we are going to clear our GUI graphics system.
        gui_window->setActive(true);
        gui_window->clear();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        glClear(GL_COLOR_BUFFER_BIT);
#pragma clang diagnostic pop
        nk_sfml_render(NK_ANTI_ALIASING_ON);
        gui_window->display();

        // Clear the window
        m_window->clear();
        // Updates specified by the user
        m_updateFunc(this);
        handleGUIInput();
        // Additional drawing specified by user
        m_drawFunc(this);
        // Update the texture
        // Note: This can be done in the 'draw call'
        // Draw to the canvas
        m_window->draw(*m_sprite);
        // Display the canvas
        m_window->display();

    }
}

void App::addClient(TCPClient *client) {
    m_client = client;
    m_client->joinServer(m_client->getIpAddress(), m_client->getPort());
}

TCPClient *App::getClient() {
    return m_client;
}

sf::Uint8 App::getColorNumber(sf::Color color) {
    if (color == sf::Color::Black) {
        return 1;
    } else if (color == sf::Color::White) {
        return 2;
    } else if (color == sf::Color::Red) {
        return 3;
    } else if (color == sf::Color::Green) {
        return 4;
    } else if (color == sf::Color::Blue) {
        return 5;
    } else if (color == sf::Color::Yellow) {
        return 6;
    } else if (color == sf::Color::Magenta) {
        return 7;
    } else if (color == sf::Color::Cyan) {
        return 8;
    } else {
        return -1;
    }
}

sf::Uint8 App::getRadius() const {
    return brushRadius;
}


void App::addToUndo(Command *c) {
    m_commands.push_front(c);
}

/*! \brief Increase brush radius by 1
 */
void App::incrementBrushRadius() {
    brushRadius++;
}

/*! \brief Decrease brush radius by 1 iff this results in positive number
 */
void App::decrementBrushRadius() {
    if (brushRadius > 1) {
        brushRadius--;
    }

}
