#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "tinyshell.h"

using namespace std;

static bool fork_pipe_redirect(const vector<string>& command, io pipes[2])
{
    if (fork() == CHILD)
    {
        vector<char*> argv;
        for (auto& s : command) argv.push_back(const_cast<char*>(s.c_str()));
        argv.push_back(nullptr);

        if (redirect_in(argv.data()) && connect(pipes) && redirect_out(argv.data()))
            return true;
    }
    return false;
}

void execute(const vector<string>& command)
{
    static io pipes[2];
    bool is_child_process;

    if (pipe_count && pipe(pipes[CURRENT]) == ERROR)
        exit_error("pipe");

    is_child_process = fork_pipe_redirect(command, pipes);

    if (is_child_process)
    {
        vector<char*> argv;
        for (auto& s : command) argv.push_back(const_cast<char*>(s.c_str()));
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        exit_error("execvp");
    }

    if (!is_background)
        while (wait(nullptr) >= 0);

    close_(pipes);
    alternate(reinterpret_cast<int**>(pipes));
}
