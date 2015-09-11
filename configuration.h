#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::cout;

class Configuration {
    public:
        Configuration(std::string path);
        /* Parse the configuration. This must be called before you try to get anything from it. */
        bool Parse();
        /* Get a string from the configuration, by key. Returns true and places it into out if it was found. 
         * Returns false if not found.
         */
        bool GetString(std::string key, std::string &out);
        /* Get an int from the configuration, by key. Returns true and places it into out if it was found and
         * a valid int. Returns false if it was not found or was not convertable to an int.
         */
        bool GetInt(std::string, int &out);
    private:
        std::string file;
        std::map<std::string, std::string> config;
};