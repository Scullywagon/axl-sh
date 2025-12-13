#include "../include/config.hpp"
#include <fstream>

void Config::load()
{
    std::ifstream config("~/.config/axl/conf.axl");

    for (std::string line; getline(config, line);)
    {
        if (line == "ssh-agent = true")
        {
            Config::startSshAgent();
        }
    }
}

void Config::startSshAgent()
{
    if (system("pgrep ssh-agent > /dev/null 2>&1") == 0)
        return;

    FILE *pipe = popen("ssh-agent -s", "r");
    if (!pipe)
        return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe))
    {
        std::string line(buffer);
        auto eq = line.find('=');
        auto semi = line.find(';', eq);
        if (eq != std::string::npos && semi != std::string::npos)
            setenv(line.substr(0, eq).c_str(), line.substr(eq + 1, semi - eq - 1).c_str(), 1);
    }

    pclose(pipe);
}
