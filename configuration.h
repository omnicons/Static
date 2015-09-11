#include <map>
#include <string>
#include <fstream>
#include <iostream>

using std::cout;

class Configuration {
    public:
        Configuration(std::string path);
        bool Parse();
        bool GetString(std::string key, std::string &out);
        bool GetInt(std::string, int &out);
    private:
        std::string file;
        std::map<std::string, std::string> config;
};