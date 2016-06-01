/*  Author:     Tomas Ochoa
 *  Date:       3/31/15
 *  Purpose:        The purpose of this cpp file is to implement the socket class to
 *              defined in "socket.h" This implementation is derrived from Rob Tougher's socket
 *              class file from his article "Linux Socket Programming in C++"
 *
 *  Article:    http://tldp.org/LDP/LG/issue74/tougher.html#3.4
 *
 *  Code
 *  Reference:  http://tldp.org/LDP/LG/issue74/misc/tougher/Socket.cpp.txt
*/

#include "socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iomanip>
#include <iostream>

using namespace std;

// Default Constructor
Socket::Socket() :
    sockDescriptor(-1)
{
    memset(&DictServer,0,sizeof(DictServer));
}

// Default destructor
Socket::~Socket()
{
    if(isValid())
        ::close(sockDescriptor);
}

// Create a socket
bool Socket::create()
{
    // Set the descriptor to the connect address and connection type
    sockDescriptor = socket(AF_INET,SOCK_STREAM,0);

    // If Conenction failed return false
    if(!isValid())
        return false;

    // Time to wait
    int on = 1;
    if(setsockopt(sockDescriptor,SOL_SOCKET,SO_REUSEADDR,(const char* ) &on,sizeof(on)) == -1)
        return false;

    return true;
}

// Bind Connection (for servers)
bool Socket::bind(const int port)
{
    // If connection failed, return false
    if(!isValid())
        return false;

    // Set the socket address to the addresses and bind
    DictServer.sin_family      = AF_INET;
    DictServer.sin_addr.s_addr = INADDR_ANY;
    DictServer.sin_port        = htons(port);

    int bindReturn = ::bind(sockDescriptor,(struct sockaddr * ) &DictServer, sizeof(DictServer));

    if(bindReturn == -1)
        return false;

    return true;
}

// Listen to the connection
bool Socket::listen() const
{
    // If connection failed, return false
    if(!isValid())
        return false;

    int listenReturn = ::listen(sockDescriptor,MAXCONNECTIONS);
    // Error check
    if(listenReturn == -1)
        return false;

    return true;
}

// Accept the connection (for server)
bool Socket::accept(Socket &newSocket) const
{
    int addressLength = sizeof(DictServer);

    newSocket.sockDescriptor = ::accept(sockDescriptor,(sockaddr *) &DictServer, (socklen_t *) &addressLength);

    // Error check
    if(newSocket.sockDescriptor <= 0)
        return false;
    else
        return true;
}

// Send a messege to the server/client
bool Socket::send(const std::string s) const
{
    int status = ::send(sockDescriptor,s.c_str(),s.size(),MSG_NOSIGNAL);
    // Error check
    if(status == -1)
        return false;
    else
        return true;
}

// Recieve messege from server/client
int Socket::recieve(std::string& s) const
{
    // Declare and create a buffer of max size
    char buffer[MAXRECV+1];

    s = "";

    // Set the buffer to a block of memmory with a max amount of MAXRECV
    memset(buffer,0,MAXRECV + 1);

    int status = ::recv(sockDescriptor,buffer,MAXRECV,0);

    // If any errors occur, display them and exit
    if(status == -1)
    {
        std::cout << "status == -1 errno == " << errno << " in Socket::recieve" << endl;
        return 0;
    } // fatal error
    else if(status == 0)
        return 0;
    else // recieve the mesegeand store it into the buffer
    {
        s = buffer;
        return status;
    }
}

// Connect to a server/client
bool Socket::connect(const std::string host, const int port)
{
    // If connection failed, return false
    if(!isValid())
        return false;

    // Set the addresses to connect properly
    DictServer.sin_family      = AF_INET;
    DictServer.sin_addr.s_addr = inet_addr(host.c_str());
    DictServer.sin_port        = htons(port);

    int status = inet_pton(AF_INET,host.c_str(), &DictServer.sin_addr.s_addr);

    // Error check
    if(errno == EAFNOSUPPORT)
        return false;

    // Set the status
    status = ::connect(sockDescriptor,(sockaddr *) &DictServer,sizeof(DictServer));

    //Error check
    if(status == 0)
        return true;
    else
        return false;
}

// server block or non block
void Socket::setNonBblocking(const bool b)
{
    // declare operations
    int opts;

    opts = fcntl(sockDescriptor,F_GETFL);

    // Check the result
    if(opts < 0)
        return;

    if(b)
        opts = (opts | O_NONBLOCK);
    else
        opts = (opts & ~O_NONBLOCK);

    fcntl(sockDescriptor,F_SETFL,opts);
}
