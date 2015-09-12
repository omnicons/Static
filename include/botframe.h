#include "irc.h"
#include "ircparse.h"
#include "configuration.h"

#include <iostream>

using std::cout;

class Bot {
    public:
        Bot();
        ~Bot();
        
        void Go();
        /* Shortcut to write to IRC connection */
        void Raw(std::string line);
    private:
        std::string nick;
        Configuration *config;
        IrcConnection *conn;
};