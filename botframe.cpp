#include "botframe.h"

Bot::Bot() {
    std::string host;
    int port;
    
    this->config = new Configuration("bot.config");
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
    std::string line;
    this->conn->Connect();
    
    this->conn->WriteLine("NICK test");
    this->conn->WriteLine("USER test * * :test");
    
    while (true) {
        if (this->conn->ReadLine(line)) {
            cout << "--> " << line << "\n";
        }    
    }
}