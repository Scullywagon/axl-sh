#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

#include "readline/history.h"
#include "readline/readline.h"

#include "../include/config.hpp"
#include "../include/env.hpp"
#include "../include/exec.hpp"
#include "../include/parse.hpp"

extern char **environ;
bool is_login_shell = false;

std::string prompt()
{
    std::string user = std::getenv("USER");
    auto cwd = std::filesystem::current_path();

    std::string home = std::getenv("HOME");
    std::string pathStr = cwd.string();

    if (pathStr.compare(0, home.size(), home) == 0)
        pathStr.replace(0, home.size(), "~");

    return "[" + pathStr + "] " + user + " : ";
}

int main(int argc, char **argv)
{
    Config::load();
    if (argv[0][0] == '-')
    {
        is_login_shell = true;
    }
    if (Parse::hasFlag(argc, argv, "--login"))
    {
        is_login_shell = true;
    }

    if (is_login_shell)
    {
    }

    while (true)
    {
        char *input = readline(prompt().c_str());
        add_history(input);

        std::vector<std::string> args = Parse::input(std::string(input), ' ');

        if (args[0] == "exit")
            return 0;

        Exec::run(args);
    }

    return 0;
}
