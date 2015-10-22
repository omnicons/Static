#include "utils.h"

std::vector<std::string> split_string(std::string str, std::string delimiter) {
    size_t pos;
    size_t delim_len = delimiter.length();
    std::vector<std::string> split;
    
    while ((pos = str.find(delimiter)) != std::string::npos) {
        split.push_back(str.substr(0, pos));
        str = str.substr(pos + delim_len);
    }
    
    split.push_back(str);
    
    return split;
}

std::string strtolower(std::string str) {
    return boost::to_lower_copy<std::string>(str);
}
