/**
 *  @file   TCPServer.hpp
 *  @brief  Represents a server for a drawing app.
 *  @author Ellah
 *  @date   2021-12-05
 ***********************************************/
#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

// We are going to build a TCP Server abstracted
// over SFML's sockets. We can think of this as a 'Network Manager' class for us.
// Building a general network manager is really cool, because
// we can reuse it for other projects. And depending on our domain,
// we can potentially write this part of the code in a completely
// different language. Remember, in our networking application we
// are just passing data back and forth between two endpoints after all.

// Some nice resources to learn more about packet sending can be found:
// https://www.sfml-dev.org/tutorials/2.5/network-packet.php


// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Command.hpp"

// Other standard libraries
#include <string>
#include <vector>
#include <map>


// Create a non-blocking TCP server
class TCPServer {
public:
    // Default Constructor
    TCPServer();
    // Default Destructor
    ~TCPServer();
    // Start the server
    bool start();
    bool connectServer(std::string name, sf::IpAddress address, unsigned short port);
    // Stops the server from running and removes all clients
    int stop();
    unsigned short getPort();
    int getClients();
    bool m_start;

private:

    // What to do when the client joins the server
    int joiningClient(sf::TcpSocket *client);

    // What to do when the client leaves the server
    int removeClient(sf::TcpSocket *socket);

    //int broadcastMessage(std::string s, sf::IpAddress ip);
    // Sends a new packet to all connected clients
    int broadcastCommandPacket(const std::string &username, sf::Packet packet);

    // Information about the server
    int m_status;
    std::string m_name;
    unsigned short m_port;
    // SocketSelector
    sf::SocketSelector m_selector;
    // Ip Address for our TCP Server
    sf::IpAddress m_ipAddress;
    // A TCP Socket for our server
    sf::TcpSocket m_socket;
    sf::TcpListener m_listener;
    // Dictionary to store each clients commands
    // Vector to keep track of clients
    std::vector<sf::TcpSocket *> m_clients;
    // Store packets and client ids
    std::map<std::string, std::vector<sf::Packet>> client_commands;

    // A data structure to hold all of the clients.
    std::map<std::string, sf::TcpSocket *> m_activeClients;
    // A data structure to hold all of the packets
    std::vector<sf::Packet> m_packetHistory;
    // A data structure to hold all of the messages sent
    std::vector<Command> m_commandshistory;

};

#endif
