#include "botframe.h"

Bot::Bot() {
    std::string host;
    int port;
    
    this->config = new Configuration("bot.config");
    if (!this->config->GetString("irc_nick", this->nick)) {
        throw std::runtime_error("Failed to load IRC nickname from config!");
    }
    if (this->config->GetString("irc_host", host) && this->config->GetInt("irc_port", port)) {
        this->conn = new IrcConnection(host, port);
    } else {
        /* Failed to load config properly */
        throw std::runtime_error("Failed to load IRC hostname and port from config!");
    }
}

Bot::~Bot() {
    delete this->config;
    delete this->conn;
}

void Bot::Go() {
    std::string raw;
    this->conn->Connect();
    
    this->Raw("NICK " + this->nick);
    this->Raw("USER " + this->nick + " * * :" + this->nick); /* XXX: Don't use nick as ident and realname. */
    
    while (true) {
        if (this->conn->ReadLine(raw)) {
            Line ln(raw); /* Parse the line using our line parser */
            cout << "--> " << raw << "\n";
            
            if (ln.command == "PING" && ln.params.size() > 0) {
                this->Raw("PONG :" + ln.params[0]);
            }
        }    
    }
}

void Bot::Raw(std::string line) {
    cout << "<-- " << line << "\n";
    this->conn->WriteLine(line);
}