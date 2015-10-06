#include <errno.h>
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
#include <stdexcept>

#include "linebuf.h"

using std::cout;

class IrcConnection {
    public:
        IrcConnection(std::string host, int port);
        ~IrcConnection();
        void Connect();
        void Disconnect();
        void WriteLine(std::string line);
        bool ReadLine(std::string &line);
    private:
        std::string host;
        int port;
        int sock;
        LineBuffer *buffer;
};