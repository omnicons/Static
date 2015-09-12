#include "irc.h"
#include "configuration.h"

#include <iostream>

using std::cout;

class Bot {
    public:
        Bot();
        ~Bot();
        
        void Go();
    private:
        Configuration *config;
        IrcConnection *conn;
};