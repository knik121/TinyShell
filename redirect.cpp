#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "tinyshell.h"

using namespace std;

bool redirect_in(char** args)
{
    for (int i = 0; args[i]; ++i)
    {
        if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd == -1) exit_error("redirect_in: open");
            dup2(fd, STDIN_FILENO);
            close(fd);
            return true;
        }
    }
    return true;
}

bool redirect_out(char** args)
{
    for (int i = 0; args[i]; ++i)
    {
        int fd = -1;
        if (strcmp(args[i], ">") == 0)
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else if (strcmp(args[i], ">>") == 0)
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);

        if (fd != -1)
        {
            dup2(fd, STDOUT_FILENO);
            close(fd);
            return true;
        }
    }
    return true;
}