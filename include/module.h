#pragma once
#include "ircparse.h"

class Bot;
class Module {
    public:
        Module() { }
        virtual ~Module() { }
        virtual void OnIRCRaw(Line line) { }
        Bot *bot;
};