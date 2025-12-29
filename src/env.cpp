#include <string>

#include "../include/env.hpp"

std::string Env::get(std::string var)
{
    std::string res = var.substr(1);
    const char *val = getenv(res.c_str());
    if (val)
    {
        return std::string(val);
    }
    else
    {
        return "";
    }
}

void Env::unset(std::vector<std::string> args)
{
    if (args.size() == 1)
        return;
    for (int i = 1; i < args.size(); i++)
    {
        unsetenv(args[i].c_str());
    }
}

void Env::set(std::vector<std::string> args)
{
    if (args.size() != 3)
        return;
    for (int i = 1; i < args.size(); i++)
    {
        setenv(args[1].c_str(), args[2].c_str(), 1);
    }
}

