#include <fstream>
#include <iostream>

#include "../include/config.hpp"
#include "../include/exec.hpp"
#include "../include/parse.hpp"

void Config::load()
{
    const char *home = std::getenv("HOME");
    if (!home)
    {
        return;
    }

    std::ifstream config(std::string(home) + "/.config/axl/conf.axl");

    for (std::string line; getline(config, line);)
    {
        std::cout << "loading line: " << line << '\n';
        std::vector<std::string> args = Parse::input(line, ' ');
        Exec::run(args);
    }
}
