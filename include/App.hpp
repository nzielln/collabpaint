/**
 *  @file   App.hpp
 *  @brief  App class interface
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/
#ifndef APP_HPP
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include <map>
// Project header files
#include "Command.hpp"
#include "TCPClient.hpp"

#include "CompositeCommand.hpp"
using namespace std;

// Some values for our GUI
enum {
    DRAW_MODE, ERASE_MODE
};
struct Mode {
    const char *label;
    int mode;
};

struct PresetColor {
    const char *label;
    sf::Color color;
};

// Singleton for our Application called 'App'.
class App {
private:

// Member variables
    // Queue stores the next command to do.
    deque<Command *> m_commands;
    // Stack that stores the last action to occur.
    stack<Command *> m_undo;
    // Main image
    sf::Image *m_image;
    // Create a sprite that we overlay on top of the texture.
    sf::Sprite *m_sprite;
    // Texture sent to the GPU for rendering
    sf::Texture *m_texture;
    // Our rendering window
    sf::RenderWindow *m_window;

    // Our clock for measuring re-renders
    sf::Clock *m_clock;
    TCPClient *m_client;
    sf::RenderWindow *gui_window;

// Store the address of our function pointer for each of the callback functions.
    void (*m_updateFunc)(App *);
    void (*m_drawFunc)(App *);

    void executeCommand(Command *c);

    void drawLayout();
    void handleGUIInput();

public:
// Member Variables
    unsigned int mouseX, mouseY;
    int selectedMode = DRAW_MODE;
    sf::Uint8 brushRadius;
    sf::Color selectedColor = sf::Color::Black;
    sf::Color backgroundColor = sf::Color::White;
    map<string, CompositeCommand *> m_inProgressCommands;
    queue<sf::Packet> m_packets;

// Globals
    unsigned static int const MAX_REMEMBERED_COMMANDS = 100;
    unsigned static int const WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
    unsigned static int const GUI_WIDTH = 220;
    unsigned static int const FRAMES_PER_SECOND = 24;
    static const vector<Mode> PRESET_MODES;
    static const vector<PresetColor> PRESET_COLORS;

// Member functions
    //Getters
    sf::Image &getImage();
    sf::Texture &getTexture();
    sf::RenderWindow &getWindow();
    sf::Clock &getClock();
    sf::Color getBGColor();
    TCPClient *getClient();

    int getMode();
    [[nodiscard]] sf::Uint8 getRadius() const;
    static sf::Uint8 getColorNumber(sf::Color color);

    //Setters
    void setMode(int newMode);
    void setBGColor(sf::Color newBGColor);

    //Other
    //Constructor
    App(void (*updateFunction)(App *), void (*drawFunction)(App *));

    void addClient(TCPClient *client);

    void startComposite(const string &username, CompositeCommand *c);
    void endComposite(const string &username);
    void addToComposite(const string &username, Command *c);
    void addCommand(Command *c);
    void undoCommand();
    void redoCommand();

    void incrementBrushRadius();
    void decrementBrushRadius();

    void destroy();
    void loop();


};

#endif
