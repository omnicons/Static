#include "irc.h"

IrcConnection::IrcConnection(std::string host, int port) { 
    this->host = host;
    this->port = port;
    this->buffer = new LineBuffer();
}

IrcConnection::~IrcConnection() {
    this->Disconnect();
    delete this->buffer;
}

void IrcConnection::Connect() {
    int res;
    struct addrinfo hints; 
	struct addrinfo *servinfo; 
	
	memset(&hints, 0, sizeof(hints)); 
	
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE; 
	
	if ((res = getaddrinfo(this->host.c_str(), std::to_string(this->port).c_str(), &hints, &servinfo)) != 0) { 
	    throw std::runtime_error(std::string("Error occured resolving address of IRC server: ") + gai_strerror(res));
	}
	
	if ((this->sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
	    freeaddrinfo(servinfo);
	    throw std::runtime_error(std::string("Failed to create socket: ") + strerror(errno));
	}
		
	if ((res = connect(this->sock, servinfo->ai_addr, servinfo->ai_addrlen)) == -1) { 
		freeaddrinfo(servinfo);
		throw std::runtime_error(std::string("Failed to connect to IRC server: ") + strerror(errno));
	}
	
	freeaddrinfo(servinfo);
    cout << "Successfully connected to IRC.\n";	
}

void IrcConnection::WriteLine(std::string line) {
    std::stringstream ss;
    const char *c_str;
    int res;
    
    ss << line << "\r\n";
    
    c_str = ss.str().c_str();
    
    /* TODO: Retry sending if it sends less than all the bytes */
    if ((res = send(this->sock, c_str, strlen(c_str), 0)) < 1) {
        throw std::runtime_error("Failed to write data to socket!");
    }
}

bool IrcConnection::ReadLine(std::string &line) {
    int res;
    char buf[4096];

    if (this->buffer->GetLine(line)) { /* We already had a line buffered */
        return true;
    }
    
    /* No line buffered yet, read some more data from the server and hope. */
    
    memset(buf, 0, sizeof(buf));
    res = recv(this->sock, buf, sizeof(buf), 0);
    
    if (res == -1) {
        throw std::runtime_error("Error reading from IRC server!\n");
    }
    
    if (res == 0) { /* 0 bytes read means connection closed */
        throw std::runtime_error("IRC server closed the connection on us!\n");
    }
    
    this->buffer->Append(std::string(buf));
    
    if (this->buffer->GetLine(line)) { /* Try again to see if there was a new line in the data we just read */
        return true;
    }
    
    return false;
}

void IrcConnection::Disconnect() {
    close(this->sock);
}