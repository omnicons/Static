#pragma once
#include <string>
#include <iostream>

using std::cout;

class LineBuffer {
    public:
        void Append(std::string data);
        bool HasLine();
        bool GetLine(std::string &out);
    private:
        std::string buffer;
};