/*  Author:     Tomas Ochoa
 *  Date:       3/31/15
 *  Purpose:        This class header file defines a class for the client socket. This class
 *              file derrives from Rob Tougher's ClientSocket class file from his article
 *              "Linux Socket Programming in C++"
 *
 *
 *  Article:    http://tldp.org/LDP/LG/issue74/tougher.html#3.4
 *
 *  Code
 *  Reference:  http://tldp.org/LDP/LG/issue74/misc/tougher/ClientSocket.h.txt
*/
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socket.h"

class ClientSocket:private Socket
{
    public:
        // Default constructor
        ClientSocket(std::string host,int port);
        virtual ~ClientSocket(){};

        // Overloaded operators to make sending and recieving data
        // easier and also allows for neater code
        const ClientSocket& operator << ( const std::string& ) const;
        const ClientSocket& operator >> ( std::string& ) const;
};

#endif // CLIENTSOCKET_H
