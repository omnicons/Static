#include "irc.h"
#include "configuration.h"

int main(int argc, char *argv[]) {
    /* IrcConnection *conn = new IrcConnection("irc.canternet.org", 6667);
    conn->Connect();
    delete conn; */
    std::string host;
    Configuration *conf = new Configuration("bot.config");
    conf->Parse();
    if (conf->GetString("irc_host", host)) {
        cout << "irc_host is: " << host << "\n";
    } else {
        cout << "Failed to lookup irc_host in config!\n";
    }
    
    delete conf;
    return 0;
}