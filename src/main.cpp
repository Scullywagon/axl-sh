#include <filesystem>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

std::vector<std::string> splitInput(std::string input, char delim)
{
    std::vector<std::string> result;
    std::string sub_str = "";

    for (char x : input)
    {
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

void exec(std::vector<std::string> args)
{
    std::vector<char *> c_args;
    for (std::string &word : args)
    {
        c_args.push_back(const_cast<char *>(word.c_str()));
    }
    c_args.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(c_args[0], c_args.data());
        exit(1);
    }
    else
    {
        waitpid(pid, nullptr, 0);
    }
}

void changeDir(std::vector<std::string> args)
{
    std::string dir = "~/";
    if (args.size() > 1)
    {
        dir = args[1];
    }

    chdir(dir.c_str());
}

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

int main()
{
    while (true)
    {
        std::cout << prompt();
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> args = splitInput(input, ' ');

        if (args[0] == "cd")
        {
            changeDir(args);
            continue;
        }

        exec(args);
    }
}
