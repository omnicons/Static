#include "configuration.h"
using std::cout;

Configuration::Configuration(std::string file) {
    this->file = file;
    this->Parse();
}

void Configuration::Parse() {
    std::ifstream is(this->file);
    std::string line;
    
    if (!is.is_open()) { /* File doesn't exist or is inaccessible. */
        throw std::runtime_error("Failed to open configuration file " + this->file);
    }
    
    while (getline(is, line)) {
        std::string key;
        std::string value;
        bool in_value = false;
        
        if (line.empty()) {
            continue;
        }
        
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
        if (value.length() > 0 && isspace(value[0])) {
            value = value.substr(1); /* Trim off leading space */
        }
        
        this->config[key] = value;
    }
    
    is.close();
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

bool Configuration::GetStringList(std::string key, std::vector<std::string> &out) {
    std::string str;
    
    if (!this->GetString(key, str)) {
        return false;
    }
    
    out = split_string(str, ", ");

    return true;
}