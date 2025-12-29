#pragma once
#include <string>
#include <vector>

namespace Env 
{
void set(std::vector<std::string> args);
std::string get(std::string var);
void unset(std::vector<std::string> args);
}
