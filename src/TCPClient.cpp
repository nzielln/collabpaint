/**
 *  @file   TCPClient.hpp
 *  @brief  Represents a clientt in a drawing app.
 *  @author Ellah
 *  @date   2021-12-05
 ***********************************************/

// Project header files
#include "TCPClient.hpp"
// Include standard library C++ libraries.
#include <iostream>

/*! \brief 	Client constructor
*
*/
TCPClient::TCPClient(std::string username, unsigned short port) {
    m_username = username;
    m_port = port;
}

/*! \brief 	Client destructor
*
*/
TCPClient::~TCPClient() {
    std::cout << "Client destructor called" << std::endl;
}

/*! \brief 	Connects client to server
*
*/
bool TCPClient::joinServer(sf::IpAddress serverAddress, unsigned short serverPort) {
    std::cout << "TCPClient will attemp to join server: " << std::endl;
    m_serverIpAddress = serverAddress;
    m_serverPort = serverPort;
    sf::Uint8 header = NON_COMMAND;

    // Attempt to connect to server
    int status = m_socket.connect(serverAddress, serverPort);

    std::cout << "Connection Request Sent" << std::endl;

    // If connection is not successful
    if (status != sf::Socket::Done) {
        std::cout << "Unable to bind -- Error: " << status << std::endl;
        return status;
    }

    // If connection is successful, sent first message that will be broadcasted to everyone
    std::string message = m_username + " connected to Server";
    m_packet << header << m_username;

    m_socket.send(m_packet);
    m_socket.setBlocking(false);

    // Always call this to be receiving data
    receiveData();

}

/*! \brief 	Send command to server
*
*/
int TCPClient::sendCommand(sf::Packet packet) {
    if (packet.getDataSize() > 0 && m_socket.send(packet) == sf::Socket::Done) {
        std::cout << "I, " << m_username << " sent a new packet\n";
    } else {
        std::cout << "Failed to send packet to server." << std::endl;
    }

    // Wait to get data from server
    receiveData();
}

/*! \brief 	Handles data recieved from server
*
*/
sf::Packet TCPClient::receiveData() {

    sf::Packet packet;
    sf::Uint8 header, ncolor, radius;
    std::string username;
    sf::Vector2i pos;

    int status = m_socket.receive(packet);

    switch (status) {
        // Only try to unpack if connection is Done, meaning data was sent over
        // We need to do this because status will always return something (non-blocking), including Error
        // and NotReady, which will disconnect our client. So, we want to stop trying to retreive data if
        // connection isn't Done - hope that makes sense
        case sf::Socket::Done:
            packet >> header;
            switch (header) {
                case DRAWBRUSH:
                    packet >> username >> pos.x >> pos.y >> ncolor >> radius;
                    std::cout << "Received a draw command at position (" << pos.x << ", " << pos.y << ") with radius "
                              << std::to_string(radius) << " from " << username << "\n";
                    packet << header << username << pos.x << pos.y << ncolor << radius;
                    break;
                case ERASER:
                    packet >> username >> pos.x >> pos.y;
                    std::cout << "Received an eraser command at position (" << pos.x << ", " << pos.y <<
                              ") from " << username << "\n";
                    packet << header << username << pos.x << pos.y;
                    break;
                case CLEARSCREEN:
                    packet >> username;
                    std::cout << "Received an clearscreen command\n";
                    packet << header << username;
                    break;
                case NON_COMMAND:
                    break;
                default:
                    packet >> username;
                    std::cout << "Received a command from " << username << "\n";
                    packet << header << username;
                    break;
            }
            break;
            // Otherwise, break and go back to what client was doing
        default:
            break;
    }

    // Return packet, may be empty
    return packet;

}

/*! \brief Returns client's username
*
*/
std::string TCPClient::getUsername() {
    return m_username;
}

/*! \brief 	Returns client's port
*
*/
int TCPClient::getPort() {
    return m_port;
}

/*! \brief 	Returns client's ipaddress
*
*/
sf::IpAddress TCPClient::getIpAddress() {
    return m_ipAddress;
}

/*! \brief 	Returns true if client is disconnected
*
*/
bool TCPClient::diconnected() {
    int status = m_socket.connect(m_serverIpAddress, m_serverPort);
    if (status == sf::Socket::Disconnected) {
        return true;
    }

    return false;

}

/*! \brief 	Returns client's socket
*
*/
sf::TcpSocket *TCPClient::getSocket() {
    return &m_socket;
}