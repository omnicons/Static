#include "ircparse.h"
/* Utility functions */

/* Remove whitespace from the left side (beginning) of a string.
 * Taken from http://stackoverflow.com/a/217605
 */
static inline std::string ltrim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

/* Start at the beginning of `str`, going through each character in it
 * and accumulating them into a buffer until we hit a character contained
 * in `badchars`. Once we hit such a character, stop traversing `str`
 * and return the accumulated buffer.
 */
std::string TakeWhileGood(std::string str, std::string badchars) {
	std::string out;

	for (char &c : str) {
		if (badchars.find(c) != std::string::npos) {
			break;
		}

		out += c;
	}

	return out;
}

/* Hostmask constructor: Parses an IRC hostmask. */
Hostmask::Hostmask(std::string raw) {
	if (raw.length() == 0) { /* Empty hostmask, nothing to do */
		return;
	}

	std::size_t host_sep = raw.find('@');
	bool has_other = (host_sep != std::string::npos);

	if (!has_other) { /* Just a host, no nick or user */
		this->host = raw;
		this->maskstr = raw;
		return;
	}

	std::size_t nick_sep = raw.find('!');
	bool has_user = (nick_sep != std::string::npos);
	if (!has_user) {
		this->nick = raw.substr(0, host_sep);
		this->host = raw.substr(host_sep + 1);
		this->maskstr = raw;
	} else {
		this->nick = raw.substr(0, nick_sep);
		this->user = raw.substr(nick_sep + 1, host_sep - (nick_sep + 1));
		this->host = raw.substr(host_sep + 1);
	}
}

/* Line constructor: Parses an IRC protocol line. */
Line::Line(std::string line) {
	this->linestr = line;

	if (line.length() == 0) { /* Empty line, nothing to do. */
		return;
	}

	if (line[0] == ':') { /* Hostmask prefix */
		std::size_t space = line.find(' ');
		this->hostmask = new Hostmask(line.substr(1, space));
		line = ltrim(line.substr(space));
	}

	this->command = TakeWhileGood(line, " :");

	if (this->command.length() == 0) {
		throw std::runtime_error("Tried to parse invalid line '" + this->linestr + "' - No command!");
	}

	line = ltrim(line.substr(this->command.length()));

	while (line.length() > 0) {
		std::string next_param;
		line = ltrim(line);

		if (line[0] == ':') { /* Last long param */
			next_param = line.substr(1);
			line = "";
		} else {
			next_param = TakeWhileGood(line, " ");
			line = line.substr(next_param.length());
		}

		this->params.push_back(next_param);
	}
}