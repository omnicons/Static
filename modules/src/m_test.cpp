#include "m_test.h"

ModuleTest::ModuleTest() {
    
}

void ModuleTest::OnIRCRaw(Line line) {
    cout << "Received line: " << line.linestr << "\n";
}