#pragma once
#include <string>
#include <vector>

namespace Parse
{
bool hasFlag(int argc, char **argv, const std::string &flag);
std::vector<std::string> input(std::string input, char delim);
}
