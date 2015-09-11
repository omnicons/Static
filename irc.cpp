#include "irc.h"

IrcConnection::IrcConnection(std::string host, int port) { 
    this->host = host;
    this->port = port;
}

IrcConnection::~IrcConnection() {
    this->Disconnect();
}

bool IrcConnection::Connect() {
    int res;
    struct addrinfo hints; 
	struct addrinfo *servinfo; 
	
	memset(&hints, 0, sizeof(hints)); 
	
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE; 
	
	if ((res = getaddrinfo(this->host.c_str(), std::to_string(this->port).c_str(), &hints, &servinfo)) != 0) { 
	    cout << "Error occured resolving address of IRC server: " << gai_strerror(res) << "\n";
	    return false;
	}
	
	if ((this->sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
	    cout << "Failed to create socket!\n";
	    freeaddrinfo(servinfo);
	    return false;
	}
		
	if ((res = connect(this->sock, servinfo->ai_addr, servinfo->ai_addrlen)) == -1) { 
        cout << "Failed to connect to IRC server!\n";
		freeaddrinfo(servinfo);
		return false;
	}
	
	freeaddrinfo(servinfo);
	
	cout << "Connected!\n";
	
	return true;
}

bool IrcConnection::WriteLine(std::string line) {
    std::stringstream ss;
    const char *c_str;
    int res;
    
    ss << line << "\r\n";
    
    c_str = ss.str().c_str();
    
    /* TODO: Retry sending if it sends less than all the bytes */
    if ((res = send(this->sock, c_str, strlen(c_str), 0)) < 1) {
        return false;
    }
    
    return true;
}

bool IrcConnection::ReadLine(std::string &line) {
    return false;
}

void IrcConnection::Disconnect() {
    close(this->sock);
}