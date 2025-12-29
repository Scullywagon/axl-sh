#include <string>

#include "../include/parse.hpp"

bool Parse::hasFlag(int argc, char **argv, const std::string &flag)
{
    for (int i = 0; i < argc; ++i)
    {
        if (argv[i] == flag)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> Parse::input(std::string input, char delim)
{
    std::vector<std::string> result;
    std::string sub_str = "";

    for (char x : input)
    {
        if (sub_str == "" && x == '~')
        {
            sub_str += std::getenv("HOME");
            continue;
        }
        if (x == delim)
        {
            if (sub_str != "")
            {
                result.push_back(sub_str);
            }
            sub_str = "";
            continue;
        }

        sub_str += x;
    }

    if (sub_str != "")
    {
        result.push_back(sub_str);
    }

    return result;
}
