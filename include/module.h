#pragma once
#include "ircparse.h"

class Bot;
class Module {
    public:
        Module() { }
        virtual ~Module() { }
        virtual void OnIRCRaw(Line line) { }
        virtual void OnPrivateMessage(Hostmask source, std::string message) { }
        virtual void OnChannelMessage(Hostmask source, std::string channel, std::string message) { }
        virtual void OnIRCCommand(Hostmask source, std::string target, std::string cmd, std::vector<std::string> args) { }
        Bot *bot;
};