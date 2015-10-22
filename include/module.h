#pragma once
#include <set>
#include <string>

#include "utils.h"
#include "ircparse.h"

using std::set;
using std::string;

class Bot;
class Module {
    public:
        Module() { }
        virtual ~Module() { }
        virtual void OnIRCRaw(Line line) { UNUSED(line); }
        virtual void OnPrivateMessage(Hostmask source, std::string message) { UNUSED(source); UNUSED(message); }
        virtual void OnChannelMessage(Hostmask source, std::string channel, std::string message) { UNUSED(source); UNUSED(channel); UNUSED(message); }
        virtual void OnIRCCommand(Hostmask source, std::string target, std::string cmd, std::vector<std::string> args) { UNUSED(source); UNUSED(target); UNUSED(cmd); UNUSED(args); }
        Bot *bot;
        set<string> listening_commands;
    protected:
        void RegisterCommand(string command) { listening_commands.insert(strtolower(command)); }
};
