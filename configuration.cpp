#include "configuration.h"

Configuration::Configuration(std::string file) {
    this->file = file;
}

bool Configuration::Parse() {
    std::ifstream is(this->file);
    std::string line;
    
    while (getline(is, line)) {
        std::string key;
        std::string value;
        bool in_value = false;
        
        for (char& c : line) {
            if (in_value) {
                value += c;;
            } else if (c == '=') {
                in_value = true;
            } else if (c == ' ') {
                continue;
            } else {
                key += c;
            }
        }
        value = value.substr(1);
        
        this->config[key] = value;
    }
    
    is.close();
    return true;
}

bool Configuration::GetString(std::string key, std::string &out) {
    if (this->config.find(key) != this->config.end()) {
        out = this->config[key];
        return true;
    }

    return false;
}