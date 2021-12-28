/**
 *  @file   TCPServer.hpp
 *  @brief  Represents a server for a drawing app.
 *  @author Ellah
 *  @date   2021-12-05
 ***********************************************/
#include "TCPServer.hpp"
#include "TCPClient.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <time.h>
#include <unistd.h>

/*! \brief
*
*/
TCPServer::TCPServer() {}

/*! \brief 	Connects server
*
*/
bool TCPServer::connectServer(std::string name, sf::IpAddress address, unsigned short port) {
    m_name = std::move(name);
    m_ipAddress = address;
    m_port = port;
    m_status = m_listener.listen(m_port);

    if (m_status != sf::Socket::Done) {
        std::cout << "Unable to bind -- Error: " << m_status << std::endl;
        return false;
    } else {
        m_selector.add(m_listener);
        m_start = true;
        start();
        return true;
    }

}

/*! \brief Destructor
*
*/
TCPServer::~TCPServer() {
    std::cout << "Server Destructor" << std::endl;
}

/*! \brief 	Starts the server
*   Using a TCPSelector instead of a threads, will always be checking for a new connection or if
 *   a connected client is sending data and then handles it
*/
// A little long but it kinda works so imma leave it for now :)
bool TCPServer::start() {
    std::cout << "Starting TCP Network server" << std::endl;

    while (m_start) {

        // Selector waits for a connection
        if (m_selector.wait()) {

            // Checks if it's new connection to the server
            if (m_selector.isReady(m_listener)) {
                // If it's a new connectin, creates a new client and add it to the list of clients and to the
                // selector so they can be listened to as well
                sf::TcpSocket *new_client = new sf::TcpSocket();

                if (m_listener.accept(*new_client) == sf::Socket::Done) {
                    m_clients.push_back(new_client);
                    m_selector.add(*new_client);

                    std::cout << "New connection to " << new_client->getRemoteAddress() << " has been completed.\n";

                    // Update client on all data in history
                    joiningClient(new_client);

                } else {
                    std::cout << "Could not initiate new connection from IP Address: " << new_client->getRemoteAddress()
                              << std::endl;

                    // If new connection not possible, delete client object we created
                    delete new_client;
                }

            } else {
                // Not a new connection but one of the connected clients is trying to send something
                // Find which client is trying to send data
                for (auto c: m_clients) {

                    // Possible data in the packet, may not all be filled but we have to initialize them first
                    // before unpacking from packet
                    sf::TcpSocket &client = *c;
                    std::string username;
                    sf::Vector2i pos;
                    sf::Uint8 header, ncolor, radius;

                    // Check if this clients sent a packet
                    if (m_selector.isReady(client)) {

                        // If ready, get packet sent
                        sf::Packet packet;
                        std::map<std::string, sf::TcpSocket *>::iterator it;
                        m_status = client.receive(packet);

                        //Receive message
                        if (m_status == sf::Socket::Done) {
                            packet >> header >> username;

                            it = m_activeClients.find(username);

                            if (it == m_activeClients.end()) {
                                m_activeClients.insert(std::pair<std::string, sf::TcpSocket *>(username, &client));
                            }

                            if (header == DRAWBRUSH) {
                                packet >> pos.x >> pos.y >> ncolor >> radius;
                                std::cout << username << " sent a new draw packet. Position: (" << pos.x << ", "
                                          << pos.y << "), radius" << std::to_string(radius) << std::endl;
                                packet << header << username << pos.x << pos.y << ncolor << radius;
                            } else if (header == ERASER) {
                                packet >> pos.x >> pos.y;
                                std::cout << username << " sent a new erase packet. Position: (" << pos.x << ", " << pos.y << ")\n";
                                packet << header << username << pos.x << pos.y;
                            } else if (header == CLEARSCREEN) {
                                std::cout << username << " sent a new clearscreen packet\n";
                                packet << header << username;
                            } else {
                                std::cout << username << " sent a new packet\n";
                                packet << header << username;
                            }
                            // Add packet to vector of packets and broadcast it to everyone else
                            m_packetHistory.push_back(packet);
                            broadcastCommandPacket(username, packet);
                            packet.clear();
                            // If client disconnected, remove them from server
                        } else if (m_status == sf::Socket::Disconnected) {

                            //If disconnect request, handle appropriately
                            removeClient(c);
                        }

                    }
                }
            }
        }
    }

    stop();
}

/*! \brief Stops server and removes all clients
*
*/
int TCPServer::stop() {
    m_start = false;

    // Delete each socket object
    for (auto c: m_clients) {
        delete c;
    }

    // clear clients
    m_clients.clear();

    // Clear selector
    m_selector.clear();
    m_socket.disconnect();
    m_listener.close();

    return 0;
}


/*! \brief Handles a new client joining, sends them history
*
*/
int TCPServer::joiningClient(sf::TcpSocket *client) {
    std::cout << "Updating new client\n";


    // Iterate through every packet sent and send it to the client.
    for (auto &i: m_packetHistory) {
        client->send(i);
    }

    return 0;
}

/*! \brief Handles a client leaving
*
*/
int TCPServer::removeClient(sf::TcpSocket *socket) {
    std::map<std::string, sf::TcpSocket *>::iterator it;
    sf::TcpSocket toremove;
    for (it = m_activeClients.begin(); it != m_activeClients.end(); ++it) {
        if (it->second == socket) {
            it->second->disconnect();
            m_selector.remove(*it->second);
            m_activeClients.erase(it->first);
            delete it->second;
            break;
        }
    }

    for (auto i = 0; i < m_clients.size(); i++)
        if (m_clients[i] == socket) {
            m_selector.remove(*m_clients[i]);
            break;
        }

    std::remove(m_clients.begin(), m_clients.end(), socket);

    return 0;
}

/*! \brief Sends a packet to all connected clients
*
*/
int TCPServer::broadcastCommandPacket(const std::string &username, sf::Packet packet) {
    std::cout << "FROM: " << username << std::endl;

    // Send the data to all clients
    for (auto &m_activeClient: m_activeClients) {
        // TODO - Don't send it to the client that just sent it...
        if (m_activeClient.first != username) {
            std::cout << "SENDING TO: " << m_activeClient.first << std::endl;
            sf::TcpSocket &client = *m_activeClient.second;
            if (client.send(packet) != sf::Socket::Done) {
                std::cout << "Could not send packet on broadcast\n";
            } else {
                std::cout << "Packet sent\n";
            }
        }
    }
    return 0;
}

/*! \brief 	Returns number of clients connected to server
*
*/
int TCPServer::getClients() {
    return (int)m_activeClients.size();
}

/*! \brief 	Returns server's port
*
*/
unsigned short TCPServer::getPort() {
    return m_port;
}