#include "botframe.h"

Bot::Bot() {
    std::string host;
    int port;
    
    this->config = new Configuration("bot.config");
    if (!this->config->GetString("irc_nick", this->nick) || !this->config->GetString("irc_ident", this->ident) || !this->config->GetString("irc_realname", this->realname)) {
        throw std::runtime_error("Failed to load IRC identity from config!");
    }
    
    this->config->GetStringList("irc_channels", this->channels); /* If this fails, we'll just assume we aren't joining any channels. */
    
    if (this->config->GetString("irc_host", host) && this->config->GetInt("irc_port", port)) {
        this->conn = new IrcConnection(host, port);
    } else {
        /* Failed to load config properly */
        throw std::runtime_error("Failed to load IRC hostname and port from config!");
    }
    
    this->LoadModules();
}

Bot::~Bot() {
    delete this->config;
    delete this->conn;
}

void Bot::Go() {
    std::string raw;
    this->conn->Connect();
    
    this->Raw("NICK " + this->nick);
    this->Raw("USER " + this->ident + " * * :" + this->realname);
    
    while (true) {
        if (this->conn->ReadLine(raw)) {
            Line ln(raw); /* Parse the line using our line parser */
            cout << "--> " << raw << "\n";
            
            
            if (ln.command == "PING" && ln.params.size() > 0) { /* Ping response */
                this->Raw("PONG :" + ln.params[0]);
            } else if (ln.command == "001") { /* RPL_WELCOME: Registered with the network */
                for (std::string &channel : this->channels) {
                    this->Join(channel);
                }              
            }
            
            for (Module *&mod : this->modules) {
                mod->OnIRCRaw(ln);
            }
        }    
    }
}

void Bot::Raw(std::string line) {
    cout << "<-- " << line << "\n";
    this->conn->WriteLine(line);
}

void Bot::Join(std::string channel) {
    this->Raw("JOIN " + channel);
}


void Bot::LoadModules() {
    this->modules.push_back(new ModuleTest());
}