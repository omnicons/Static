#include "m_test.h"

ModuleTest::ModuleTest() {
    cout << "Test module has been loaded!\n";
}

void ModuleTest::OnIRCRaw(Line line) {
    cout << "Received line: " << line.linestr << "\n";
}