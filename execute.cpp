#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "tinyshell.h"

using namespace std;

void execute(const std::vector<std::string>& command) {
    static io pipes[2];

    if (pipe_count && pipe(pipes[CURRENT]) == ERROR)
        exit_error("pipe");

    pid_t pid = fork();
    if (pid == CHILD) {
        std::vector<std::string> args = command;

        if (redirect_in(args) && connect(pipes) && redirect_out(args)) {
            std::vector<char*> c_args;
            for (auto& arg : args)
                c_args.push_back(const_cast<char*>(arg.c_str()));
            c_args.push_back(nullptr);

            execvp(c_args[0], c_args.data());
            exit_error("execvp");
        }
    }

    if (!is_background)
        while (wait(NULL) >= 0);

    close_(pipes);
    alternate((int**)pipes);
}
