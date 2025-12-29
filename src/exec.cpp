#include <iostream>
#include <ostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "../include/env.hpp"
#include "../include/exec.hpp"

void Exec::run(std::vector<std::string> args)
{
    if (args[0] == "cd")
        return Exec::cd(args);
    else if (args[0] == "set")
        return Env::set(args);
    else if (args[0] == "unset")
        return Env::unset(args);

    if (args.empty())
    {
        std::cerr << "no command provided\n";
        return;
    }
    std::vector<char *> c_args;
    for (std::string &word : args)
    {
        if (word.size() > 1 && word[0] == '$')
        {
            std::cout << Env::get(word) << std::endl;
            word = Env::get(word);
        }
        c_args.push_back(const_cast<char *>(word.c_str()));
    }
    c_args.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "fork failed, cannot execute\n";
    }

    if (pid == 0)
    {
        if (execvp(c_args[0], c_args.data()) == -1)
        {
            std::cerr << args[0] + ": command not found\n";
        }
    }
    else
    {
        waitpid(pid, nullptr, 0);
    }
}

void Exec::cd(std::vector<std::string> args)
{
    std::string dir = std::getenv("USER");
    if (args.size() > 1)
    {
        dir = args[1];
    }

    chdir(dir.c_str());
}
