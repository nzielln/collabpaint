/**
 *  @file   TCPServer.hpp
 *  @brief  Represents a server for a drawing app.
 *  @author Ellah
 *  @date   2021-12-05
 ***********************************************/
#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Command.hpp"

// Other standard libraries
#include <string>
#include <vector>
#include <map>
using namespace std;

// Create a non-blocking TCP server
class TCPServer {

private:

    // What to do when the client joins the server
    int joiningClient(sf::TcpSocket *client);

    // What to do when the client leaves the server
    int removeClient(sf::TcpSocket *socket);

    // Sends a new packet to all connected clients
    int broadcastCommandPacket(const string &username, sf::Packet packet);

    // Information about the server
    int m_status;
    string m_name;
    unsigned short m_port;
    // SocketSelector
    sf::SocketSelector m_selector;
    // Ip Address for our TCP Server
    sf::IpAddress m_ipAddress;
    // A TCP Socket for our server
    sf::TcpSocket m_socket;
    sf::TcpListener m_listener;
    // Map to store each clients commands
    // Vector to keep track of clients
    vector<sf::TcpSocket *> m_clients;
    // Store packets and client ids
    map<string, vector<sf::Packet>> client_commands;

    // A data structure to hold all of the clients.
    map<string, sf::TcpSocket *> m_activeClients;
    // A data structure to hold all of the packets
    vector<sf::Packet> m_packetHistory;
    // A data structure to hold all of the messages sent
    vector<Command> m_commandshistory;

public:
    //Member Variables
    bool m_start;

    //Member Functions
    // Default Constructor
    TCPServer();
    // Default Destructor
    ~TCPServer();

    // Stops the server from running and removes all clients
    int stop();
    // Start the server
    void start();
    //Connect server to port
    bool connectServer(string name, sf::IpAddress address, unsigned short port);

    //Getters
    int getClients();
    unsigned short getPort() const;

};

#endif
