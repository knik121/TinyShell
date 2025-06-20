#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <csignal>
#include "tinyshell.h"
#include "job.h"

using namespace std;

pid_t fg_pgid = -1;
void execute(const vector<string>& command) {
    static io pipes[2];

    if (pipe_count && pipe(pipes[CURRENT]) == ERROR)
        exit_error("pipe");

    pid_t pid = fork();

    if (pid == CHILD) {
        setpgid(0, 0);  // Create a new process group

        vector<string> args = command;
        if (redirect_in(args) && connect(pipes) && redirect_out(args)) {
            vector<char*> c_args;
            for (auto& arg : args)
                c_args.push_back(const_cast<char*>(arg.c_str()));
            c_args.push_back(nullptr);

            execvp(c_args[0], c_args.data());

            // Only if exec fails
            perror(("Command not found: " + command[0]).c_str());
            exit_error("execvp");
        }
    }
    else if (pid > 0) {
        setpgid(pid, pid);  // Set child's pgid to its pid
        fg_pgid = pid;
        if (is_background) {
            add_job(pid, command[0]);  // Track background job
        } else {
            // Foreground job: Give terminal control to the child
            tcsetpgrp(STDIN_FILENO, pid);

            int status;
            waitpid(pid, &status, WUNTRACED);  // WUNTRACED for Ctrl+Z
            // Return terminal control to shell
            tcsetpgrp(STDIN_FILENO, getpgrp());
            fg_pgid = -1;
            // If the process exited (not stopped), clean up
            if (!WIFSTOPPED(status)) {
                remove_job(pid);
            }
        }
    } else {
        exit_error("fork");
    }

    close_(pipes);
    alternate((int**)pipes);
}
