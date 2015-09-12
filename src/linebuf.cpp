#include "linebuf.h"

void LineBuffer::Append(std::string data) {
    this->buffer += data;
}

bool LineBuffer::HasLine() {
    return this->buffer.find('\n') != std::string::npos;
}

bool LineBuffer::GetLine(std::string &out) {
    std::string line;
    std::size_t pos = this->buffer.find('\n');
    
    if (pos == std::string::npos) {
        return false;
    }
    
    line = this->buffer.substr(0, pos);
    this->buffer = this->buffer.substr(pos + 1);
    
    if (line[line.length() - 1] == '\r') {
        line = line.substr(0, line.length() - 1);
    }

    out = line;
    return true;
}