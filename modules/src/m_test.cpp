#include "m_test.h"

ModuleTest::ModuleTest() {
    cout << "Test module has been loaded!\n";
}

void ModuleTest::OnIRCRaw(Line line) {
    cout << "Received line: " << line.linestr << "\n";
}

void ModuleTest::OnPrivateMessage(Hostmask source, std::string message) {
    cout << "Private message to us from " << source.nick << ": " << message << "\n";
}

void ModuleTest::OnChannelMessage(Hostmask source, std::string channel, std::string message) {
    cout << "Channel message to " << channel << " from " << source.nick << ": " << message << "\n";
}

void ModuleTest::OnIRCCommand(Hostmask source, std::string target, std::string cmd, std::vector<std::string> args) {
    cout << source.nick << " performed command " << cmd << " with target " << target << " and args ";
    for (std::string &arg : args) {
        cout << arg << " ";
    }
    
    cout << "\n";
}