/**
 *  @file   main.cpp
 *  @brief  Entry point into the program.
 *  @author Mike and Skye
 *  @date   2021-12-11
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// Include standard library C++ libraries.
#include <string>
#include <iostream>
#include <thread>
// Project header files
#include "App.hpp"
#include "DrawBrush.hpp"
#include "BrushStroke.hpp"
#include "ClearScreen.hpp"
#include "DrawStroke.hpp"
#include "TCPServer.hpp"
#include "TCPClient.hpp"
#include "Eraser.hpp"
#include "EraserStroke.hpp"


std::map<std::string, CompositeCommand*> incomingCommands;

void executeReceivedCommands(App *app) {
    sf::Uint8 header, ncolor, radius;
    sf::Vector2i pos;
    std::string name, username;
    DrawBrush *db;
    Eraser *er;
    sf::Color c;
    ClearScreen *cs;
    sf::Packet p = app->getClient()->receiveData();
    std::map<std::string, CompositeCommand*>::iterator it;
    p >> header >> username;

    switch (header) {
        case DRAWBRUSH:
            p >> pos.x >> pos.y >> ncolor >> radius;
            db = new DrawBrush(&app->getImage(), pos.x, pos.y, radius, App::PRESET_COLORS[ncolor - 1].color);
            db->execute();
            std::cout << "DRAW COMMAND DONE " << username << std::endl;
            app->addToUndo(db);
            break;
        case ERASER:
            p >> pos.x >> pos.y;
            er = new Eraser(&app->getImage(), pos.x, pos.y, app->getBGColor());
            er->execute();
            std::cout << "ERASE COMMAND DONE " << username << std::endl;
            app->addToUndo(er);
        case CLEARSCREEN:
            cs = new ClearScreen(&app->getImage(), app->selectedColor, app->getBGColor());
            cs->execute();
            std::cout << "CLEAR COMMAND DONE " << username << std::endl;
            app->addToUndo(cs);
        case UNDO:
            app->undoCommand();
            std::cout << "UNDO DONE " << username << std::endl;
            break;
        case REDO:
            app->redoCommand();
            std::cout << "REDO DONE " << username << std::endl;
            break;
        default:
            break;
    }
}

/*! \brief 	The update function presented can be simplified.
*		I have demonstrated two ways you can handle events,
*		if for example we want to add in an event loop.
*
*/
void update(App *app) {
    // Update our canvas
    sf::Event event;

    bool lostFocusSinceDrawing = false;

    // Update stored mouse position
    if (app->getWindow().hasFocus()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(app->getWindow());
        app->mouseX = mousePos.x;
        app->mouseY = mousePos.y;

        // For storing packet data
        sf::Packet packet;
        sf::Uint8 header;
        std::string message;
        std::string username = app->getClient()->getUsername();

        // Respond to key events
        while (app->getWindow().pollEvent(event)) {
            // Thread for handling incoming commands
            std::thread net(executeReceivedCommands, app);
            net.join();

            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        app->selectedColor = sf::Color::Black;
                        break;
                    case sf::Keyboard::Num2:
                        app->selectedColor = sf::Color::White;
                        break;
                    case sf::Keyboard::Num3:
                        app->selectedColor = sf::Color::Red;
                        break;
                    case sf::Keyboard::Num4:
                        app->selectedColor = sf::Color::Green;
                        break;
                    case sf::Keyboard::Num5:
                        app->selectedColor = sf::Color::Blue;
                        break;
                    case sf::Keyboard::Num6:
                        app->selectedColor = sf::Color::Yellow;
                        break;
                    case sf::Keyboard::Num7:
                        app->selectedColor = sf::Color::Magenta;
                        break;
                    case sf::Keyboard::Num8:
                        app->selectedColor = sf::Color::Cyan;
                        break;
                    case sf::Keyboard::Z:
                        packet.clear();
                        std::cout << "Undo" << std::endl;
                        header = UNDO;
                        packet << header << username;
                        app->getClient()->sendCommand(packet);
                        app->undoCommand();
                        break;
                    case sf::Keyboard::Y:
                        packet.clear();
                        header = REDO;
                        packet << header << username;
                        app->getClient()->sendCommand(packet);
                        app->redoCommand();
                        break;
                    case:: sf::Keyboard::Space:
                        packet.clear();
                        header = CLEARSCREEN;
                        packet << header << username;
                        app->addCommand(new ClearScreen(app));
                        app->getClient()->sendCommand(packet);
                        break;
                    case sf::Keyboard::Equal:
                        app->brushRadius++;
                        std::cout << "Radius increase" << std::endl;
                        break;
                    case sf::Keyboard::Hyphen:
                        app->brushRadius--;
                        std::cout << "Radius decrease" << std::endl;
                        break;
                    case sf::Keyboard::Escape:
                        app->getClient()->getSocket()->disconnect();
                        exit(EXIT_SUCCESS);
                    default:
                        break;
                }
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       app->getWindow().hasFocus()) { // Begin new CompositeCommand on initial mouse down
                packet.clear();
                CompositeCommand *cc;
                std::map<std::string, CompositeCommand*>::iterator it;

                if (app->selectedMode == DRAW_MODE) {
                    cc = new BrushStroke();
                    header = START_BRUSHSTROKE;
                } else if (app->selectedMode == ERASE_MODE) {
                    cc = new EraserStroke();
                    header = START_ERASERSTROKE;
                } else {
                    std::cerr << "App in unhandled mode" << std::endl;
                    return;
                }

                packet << header << username;
                app->getClient()->sendCommand(packet);
                app->startComposite(username, cc);

                //packet.clear();

                lostFocusSinceDrawing = false;
            } else if (event.type == sf::Event::LostFocus) { // End current CompositeCommand on loss of focus or mouse up
                lostFocusSinceDrawing = true;
            } else if (event.type == sf::Event::LostFocus ||
                       event.type == sf::Event::MouseButtonReleased) {

                packet.clear();

                if (app->selectedMode == DRAW_MODE) {
                    header = END_BRUSHSTROKE;
                } else if (app->selectedMode == ERASE_MODE) {
                    header = END_ERASERSTROKE;
                } else {
                    std::cerr << "App in unhandled mode" << std::endl;
                    return;
                }

                packet << header << username;

                app->getClient()->sendCommand(packet);
                app->endComposite(username);

            }
        }

        // Respond to mouse pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (lostFocusSinceDrawing) {
                app->addCommand(new BrushStroke());
                lostFocusSinceDrawing = false;
            }
            if (!(app->mouseX < 0 ||
                  app->mouseX > App::WINDOW_WIDTH ||
                  app->mouseY < 0 ||
                  app->mouseY > App::WINDOW_HEIGHT)) {

                packet.clear();
                Command *cmd;

                if (app->selectedMode == DRAW_MODE) {
                    DrawBrush *d = new DrawBrush(app);
                    cmd = d;
                    header = DRAWBRUSH;

                    // Convert color to Uint8 int
                    sf::Uint8 ncolor = App::getColorNumber(d->m_newColor);

                    packet << header << username << app->mouseX << app->mouseY << ncolor << app->brushRadius;
                } else if (app->selectedMode == ERASE_MODE) {
                    Eraser *e = new Eraser(app);
                    cmd = e;
                    header = ERASER;
                    packet << header << username << app->mouseX << app->mouseY;
                } else {
                    std::cerr << "App in unhandled mode" << std::endl;
                    return;
                }

                app->getClient()->sendCommand(packet);
                app->addToComposite(username, cmd);
            }
        }
    }

}

/*! \brief 	The draw call
*
*/
void draw(App *app) {
    sf::Time elapsed = app->getClock().getElapsedTime();

    if (elapsed.asSeconds() > (1.0 / App::FRAMES_PER_SECOND)) {
        app->getClock().restart();
        app->getTexture().loadFromImage(app->getImage());
    }
}

/*! \brief 	The entry point into our program.
*
*/
int main() {

    // Stores a role of either a server or client user.
    std::string role;

    // Set the role
    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    if (role[0] == 's' || role[0] == 'S') {
        TCPServer server;
        int port;
        std::cout << "Which port would you like to connect to? \n";
        std::cin >> port;
        bool connected = server.connectServer("Server Name", sf::IpAddress::getLocalAddress(), port);

        while (!connected) {
            std::cout << "Try a different port: \n";
            std::cin >> port;
            connected = server.connectServer("Server Name", sf::IpAddress::getLocalAddress(), port);

        }

    } else if (role[0] == 'c' || role[0] == 'C') {
        App app = App(&update, &draw);

        // Create a client and have them join
        std::string uname;
        unsigned short port;
        std::cout << "Enter your username: ";
        std::cin >> uname;
        std::cout << "Which port will you try? (e.g. 50001-50010):";
        std::cin >> port;
        TCPClient me(uname, port);
        app.getWindow().setTitle(uname + "'s Mini App");
        app.addClient(&me);
        app.loop();
        // destroy our app
        app.destroy();
    }


    return 0;
}