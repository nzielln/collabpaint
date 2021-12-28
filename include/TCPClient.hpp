/**
 *  @file   TCPClient.hpp
 *  @brief  Represents a client in a drawing app.
 *  @author Ellah
 *  @date   2021-12-05
 ***********************************************/
#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Command.hpp"

// Other standard libraries
#include <string>
#include <vector>
using namespace std;

// DRAWBRUSH   Will also hold the x, y positions, newcolor, and radius
// CLEARSCREEN Will also hold the newcolor for the background
// ERASER      Will also hold the x, y positions
enum HeaderType : sf::Uint8 {
    DRAWBRUSH, START_BRUSHSTROKE, END_BRUSHSTROKE, CLEARSCREEN, ERASER, START_ERASERSTROKE, END_ERASERSTROKE, UNDO, REDO, NON_COMMAND
};

// Create a non-blocking TCPClient
class TCPClient {
public:

    // Default Constructor
    TCPClient(string username, unsigned short port);
    // Default Destructor
    ~TCPClient();
    // Handles client attempting to join server
    bool joinServer(sf::IpAddress serverAddress, unsigned short serverPort);
    // Send data to server
    int sendCommand(sf::Packet packet);
    // Send String to server
    // Receive data from the server
    sf::Packet receiveData();
    // Get username
    string getUsername();
    // Check is client is connected to server
    bool diconnected();
    // Get IPAddress
    sf::IpAddress getIpAddress();
    // Get client Port
    int getPort();
    sf::TcpSocket *getSocket();

private:
    // Information about our user and connection
    string m_username;
    // The port which we will try to communicate from
    unsigned short m_port;
    // The server port which we will try to send information through
    unsigned short m_serverPort;
    // Our clients IP Address
    sf::IpAddress m_ipAddress;
    // The server Ip address for which we will send information to.
    sf::IpAddress m_serverIpAddress;
    // A TCP Socket for our client to create an end-to-end communication
    // with another machine in the world.
    sf::TcpSocket m_socket;
    sf::Packet m_packet;
};

#endif
