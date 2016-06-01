/*  Author:     Tomas Ochoa
 *  Date:       3/31/15
 *  Purpose:        The purpose of this header file is to define the socket class to
 *              make implementation of a client to server connection much easier and
 *              less tedious for implementations of any socket-client based programs
 *              in the future. This class file is derrived from Rob Tougher's socket
 *              class file from his article "Linux Socket Programming in C++"
 *
 *  Article:    http://tldp.org/LDP/LG/issue74/tougher.html#3.4
 *
 *  Code
 *  Reference:  http://tldp.org/LDP/LG/issue74/misc/tougher/Socket.h.txt
*/

// Necessary function headers for the socket class
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

#ifndef SOCKET_H
#define SOCKET_H

// Global variables for max amount of:
const int MAXHOSTNAME    = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV        = 100000;

class Socket
{
    public:
        Socket();
        virtual ~Socket();          // Virtual to allow to be overriden

        // Server Initialization
        bool create();
        bool bind(const int port);
        bool listen() const;
        bool accept(Socket&) const;
        // Client Initialization
        bool connect(const std::string host, const int port);
        // Data Transmission
        bool send(const std::string) const;
        int  recieve(std::string&) const;
        // Error checking
        void setNonBblocking(const bool);
        bool isValid() const
        {
            return sockDescriptor != -1;
        }
    private:
        int sockDescriptor;
        sockaddr_in DictServer;
};

#endif // SOCKET_H
