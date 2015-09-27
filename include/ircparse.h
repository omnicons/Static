#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Hostmask {
	public:
		std::string maskstr; /* Raw hostmask string */
		std::string nick; /* Nick of the user */
		std::string user; /* Ident of the user */
		std::string host; /* Hostname of the user */

		Hostmask(std::string mask);
};


class Line {
	public:
		std::string linestr; /* Raw line string */
		Hostmask *hostmask; /* Originating hostmask */
		std::string command; /* Command (numeric) */
		std::vector<std::string> params; /* List of parameters/arguments */

		Line(std::string raw);
};