/**
 *  @file   main_test.cpp
 *  @brief  Unit Tests for our program
 *  @author Mike and Skye
 *  @date   2021-19-11
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

// Include standard library C++ libraries.
#include <string>
#include <thread>
#include <utility>

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// Include standard library C++ libraries.
#include <string>
#include <iostream>

// Project header files
#include "App.hpp"
#include "Draw.hpp"
#include "DrawBrush.hpp"
#include "BrushStroke.hpp"
#include "ClearScreen.hpp"
#include "DrawStroke.hpp"
#include "Eraser.hpp"
#include "EraserStroke.hpp"
#include "TCPServer.hpp"
#include "TCPClient.hpp"


TEST_CASE("App initializes members properly & successfully destroys"){

  App app = App(nullptr, nullptr);
  sf::Image* image = &app.getImage();
  sf::Window* window = &app.getWindow();

  REQUIRE(image != nullptr);
  REQUIRE(window != nullptr);
  REQUIRE(app.mouseX == 0);
  REQUIRE(app.mouseY == 0);
  REQUIRE(app.brushRadius == 1);
  REQUIRE(app.selectedColor == sf::Color::Black);
  REQUIRE(app.backgroundColor == sf::Color::White);
  REQUIRE(app.selectedMode == 0);

  REQUIRE_NOTHROW(app.destroy());
}

TEST_CASE("Drawing commands update sf::Image") {
  App* app = new App(nullptr, nullptr);
  sf::Image* image = &app->getImage();
  app->mouseX = 10;
  app->mouseY = 15;

  REQUIRE(image->getPixel(10, 15) == sf::Color::White);
  app->addCommand(new Draw(app));
  REQUIRE(image->getPixel(10, 15) == sf::Color::Black);
  app->undoCommand();
  REQUIRE(image->getPixel(10, 15) == sf::Color::White);
  app->redoCommand();
  REQUIRE(image->getPixel(10, 15) == sf::Color::Black);
}

// TODO: This test is failing at line 98
TEST_CASE("Erasing commands update sf::Image") {
    App* app = new App(nullptr, nullptr);
    sf::Image* image = &app->getImage();
    app->selectedColor = sf::Color::Black;
    app->backgroundColor = sf::Color::White;

    // Drawing pixels
    app->mouseX = 10;
    app->mouseY = 15;
    REQUIRE(image->getPixel(10, 15) == sf::Color::White);
    app->addCommand(new Draw(app));

    REQUIRE(image->getPixel(11, 16) == sf::Color::White);
    app->mouseX = 11;
    app->mouseX = 16;
    app->addCommand(new Draw(app));

    REQUIRE(image->getPixel(12, 17) == sf::Color::White);
    app->mouseX = 12;
    app->mouseX = 17;
    app->addCommand(new Draw(app));

    // Erasing pixels
    app->mouseX = 10;
    app->mouseX = 15;
    REQUIRE(image->getPixel(10, 15) == sf::Color::Black);
    app->addCommand(new Eraser(app));
    REQUIRE(image->getPixel(10, 15) == sf::Color::White);

    app->mouseX = 11;
    app->mouseX = 16;
    REQUIRE(image->getPixel(11, 16) == sf::Color::Black);
    app->addCommand(new Eraser(app));
    REQUIRE(image->getPixel(11, 16) == sf::Color::White);

    app->mouseX = 12;
    app->mouseX = 17;
    REQUIRE(image->getPixel(12, 17) == sf::Color::Black);
    app->addCommand(new Eraser(app));
    REQUIRE(image->getPixel(12, 17) == sf::Color::White);
}

TEST_CASE("Clearing screen commands clear to correct color") {
    App* app = new App(nullptr, nullptr);
    sf::Image* image = &app->getImage();
    app->selectedColor = sf::Color::Black;
    app->backgroundColor = sf::Color::White;

    REQUIRE(app->backgroundColor == sf::Color::White);
    app->setBGColor(sf::Color::Green);
    app->addCommand(new ClearScreen(app));
    REQUIRE(app->backgroundColor == sf::Color::Green);
}

// TODO: This test is failing at line 146
TEST_CASE("App remembers exactly 100 commands to undo/redo") {
  App* app = new App(nullptr, nullptr);
  sf::Image* image = &app->getImage();

  // Draw on 101 pixels & verify
  app->mouseX = 10;
  for (int i = 1; i < 101; i++) {
    app->mouseY = i;
    app->addCommand(new Draw(app));
    REQUIRE(image->getPixel(10, i) == sf::Color::Black);
  }

  // Undo 100 times & verify
  for (int i = 101; i > 1; i--) {
    app->undoCommand();
    REQUIRE(image->getPixel(10, i) == sf::Color::White);
  }

  // Attempt to undo 101th time and verify nothing happens
  app->undoCommand();
  REQUIRE(image->getPixel(10, 1) == sf::Color::Black);

  // Redo 100 times & verify
  for (int i = 2; i < 101; i++) {
    app->redoCommand();
    REQUIRE(image->getPixel(10, i) == sf::Color::Black);
  }

  // Attempting to redo with no more undos does not fail
  REQUIRE_NOTHROW(app->redoCommand());

  app->destroy();
}

TEST_CASE("Making a new draw clears undo history") {
  App* app = new App(nullptr, nullptr);
  sf::Image* image = &app->getImage();

  // Draw at (10,15) then undo
  app->mouseX = 10;
  app->mouseY = 15;
  app->addCommand(new Draw(app));
  REQUIRE(image->getPixel(10, 15) == sf::Color::Black);
  app->undoCommand();
  REQUIRE(image->getPixel(10, 15) == sf::Color::White);

  // Draw at (20,20)
  app->mouseX = 20;
  app->mouseY = 20;
  app->addCommand(new Draw(app));

  // Redo, and verify (10,15) is unchanged
  REQUIRE(image->getPixel(10, 15) == sf::Color::White);
  app->redoCommand();
  REQUIRE(image->getPixel(10, 15) == sf::Color::White);

  app->destroy();
}

TEST_CASE("Executing/undoing DrawBrush changes pixels within a specified radius") {
    App* app = new App(nullptr, nullptr);
    sf::Image* image = &app->getImage();

    app->mouseX = 100;
    app->mouseY = 200;
    app->brushRadius = 10;
    app->selectedColor = sf::Color::Yellow;

    app->addCommand(new DrawBrush(app));

    //Check that pixels inside the circle match the draw color
    REQUIRE(image->getPixel(100, 200) == sf::Color::Yellow);
    REQUIRE(image->getPixel(109, 200) == sf::Color::Yellow);
    REQUIRE(image->getPixel(91, 200) == sf::Color::Yellow);
    REQUIRE(image->getPixel(100, 209) == sf::Color::Yellow);
    REQUIRE(image->getPixel(100, 191) == sf::Color::Yellow);

    //Check that pixels outside the circle match the old color
    REQUIRE(image->getPixel(108, 208) == sf::Color::White);
    REQUIRE(image->getPixel(109, 207) == sf::Color::White);
    REQUIRE(image->getPixel(111, 200) == sf::Color::White);
    REQUIRE(image->getPixel(91, 195) == sf::Color::White);

    app->undoCommand();
    //Check that pixels inside the circle changed back to old color
    REQUIRE(image->getPixel(100, 200) == sf::Color::White);
    REQUIRE(image->getPixel(109, 200) == sf::Color::White);
    REQUIRE(image->getPixel(91, 200) == sf::Color::White);
    REQUIRE(image->getPixel(100, 209) == sf::Color::White);
    REQUIRE(image->getPixel(100, 191) == sf::Color::White);

    //Check that pixels outside the circle still are unaffected
    REQUIRE(image->getPixel(108, 208) == sf::Color::White);
    REQUIRE(image->getPixel(109, 207) == sf::Color::White);
    REQUIRE(image->getPixel(111, 200) == sf::Color::White);
    REQUIRE(image->getPixel(91, 195) == sf::Color::White);

}

TEST_CASE("Adding to a BrushStroke draws multiple brush circles and undoing it undoes all of them") {
    App* app = new App(nullptr, nullptr);
    sf::Image* image = &app->getImage();

    app->brushRadius = 10;
    app->selectedColor = sf::Color::Yellow;

    app->startComposite("user1", new BrushStroke());

    app->mouseX = 50;
    app->mouseY = 50;
    app->addToComposite("user1", new DrawBrush(app));
    app->mouseX = 150;
    app->mouseY = 150;
    app->addToComposite("user1", new DrawBrush(app));

    //Check that pixels in both circles have flipped
    REQUIRE(image->getPixel(45, 45) == sf::Color::Yellow);
    REQUIRE(image->getPixel(155, 155) == sf::Color::Yellow);

    app->undoCommand();
    //Check that pixels in both circles have flipped back to old color
    REQUIRE(image->getPixel(155, 155) == sf::Color::White);
    REQUIRE(image->getPixel(45, 45) == sf::Color::White);
}

void networkingServerStartTask(TCPServer *server) {
    server->connectServer("SERVER", sf::IpAddress::getLocalAddress(), 8000);
}

void networkingClientTask(TCPServer *server, TCPClient *client) {
    client->joinServer(sf::IpAddress::getLocalAddress(), 8000);
}

// NOTE: Catch2 has a limitation that only one thread in the case can execute assertions
TEST_CASE("Multiple Clients can connect to server") {
    TCPServer *server = new TCPServer();

    std::thread t1(networkingServerStartTask, server);

    while (!server->m_start) {
        // Await server start
    }


    // Check server created at correct port
    REQUIRE(server->m_start == true);
    REQUIRE(server->getPort() == 8000);

    TCPClient clientA("clientA", 8000);
    std::thread t2(&networkingClientTask, server, &clientA);

    while (server->getClients() != 1) {
        // Await clientA join
    }

    // Check that initial client added
    REQUIRE(server->getClients() == 1);

    TCPClient clientB("clientB", 8000);
    std::thread t3(&networkingClientTask, server, &clientB);

    TCPClient clientC("clientC", 8000);
    std::thread t4(&networkingClientTask, server, &clientC);

    while (server->getClients() != 3) {
        // Await clientB & clientC join
    }

    // Get number of clients currently connected to server
    REQUIRE(server->getClients() == 3);

    // Check that all clients are connected
    REQUIRE(clientA.diconnected() == false);
    REQUIRE(clientB.diconnected() == false);
    REQUIRE(clientC.diconnected() == false);

    clientA.getSocket()->disconnect();

    while (!clientA.diconnected()) {
        // Await clientA disconnect
    }

    REQUIRE(clientA.diconnected() == true);

    REQUIRE(server->getClients() == 2);

    // Stopping server removes all clients
    server->stop();

    while (!(clientB.diconnected() && clientC.diconnected())) {
        // Await clientB + ClientC disconnect
    }

    REQUIRE(server->getClients() == 0);
    REQUIRE(clientB.diconnected() == true);
    REQUIRE(clientC.diconnected() == true);

}
