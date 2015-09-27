#pragma once
#include "ircparse.h"

class Bot;
class Module {
    public:
        Module() { }
        virtual void OnIRCRaw(Line line) { }
    private:
        Bot *bot;
};