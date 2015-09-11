#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#include <string>
#include <sstream>
#include <iostream>

using std::cout;

class IrcConnection {
    public:
        IrcConnection(std::string host, int port);
        ~IrcConnection();
        bool Connect();
        void Disconnect();
        bool WriteLine(std::string line);
        bool ReadLine(std::string &line);
    private:
        std::string host;
        int port;
        int sock;
};