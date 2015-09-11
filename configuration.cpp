#include "configuration.h"

Configuration::Configuration(std::string file) {
    this->file = file;
}

bool Configuration::Parse() {
    std::ifstream is(this->file);
    std::string line;
    
    if (!is.is_open()) { /* File doesn't exist or is inaccessible. */
        return false;
    }
    
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

bool Configuration::GetInt(std::string key, int &out) {
    std::string str;
    
    if (!this->GetString(key, str)) {
        return false;
    }
    
    try {
        out = std::stoi(str);
        return true;
    } catch (std::invalid_argument &ignored) {
    }
    
    return false;
}