/*  Author:     Tomas Ochoa
 *  Date:       3/31/15
 *  Purpose:        This header file is to define the socket exception class. This class
 *              derrives from Rob Tougher's SocketException class file from his article
 *              "Linux Socket Programming in C++"
 *
 *  Article:    http://tldp.org/LDP/LG/issue74/tougher.html#3.4
 *
 *  Code
 *  Reference:  http://tldp.org/LDP/LG/issue74/misc/tougher/SocketException.h.txt
*/

#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <string>

class SocketException
{
    public:
        SocketException(std::string s):m_s(s){};
        ~SocketException(){};

        std::string description()
        {
            return m_s;
        }

    private:
        std::string m_s;
};

#endif // SOCKETEXCEPTION_H
