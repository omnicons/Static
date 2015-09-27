#pragma once
#include <iostream>

#include "module.h"

using std::cout;

class ModuleTest : public Module {
    public:
        ModuleTest();
        virtual void OnIRCRaw(Line line);
};