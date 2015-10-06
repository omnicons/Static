#pragma once
#include "irc.h"
#include "module.h"
#include "ircparse.h"
#include "configuration.h"

#include "m_test.h"

#include <vector>
#include <iostream>

using std::cout;

class Bot {
    public:
        Bot();
        ~Bot();
        
        void Go();
        /* Shortcut to write to IRC connection */
        void Raw(std::string line);
        
        /* IRC protocol functions */
        void Join(std::string channel);
    private:
        std::string nick;
        std::string ident;
        std::string realname;
        std::vector<std::string> channels;
        Configuration *config;
        IrcConnection *conn;
        
        std::vector<Module *> modules;
        
        void LoadModule(Module *module);
        void LoadModules();
};