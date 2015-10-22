#pragma once
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#define UNUSED(param) (void)param

std::vector<std::string> split_string(std::string str, std::string delimiter);
std::string strtolower(std::string str);
