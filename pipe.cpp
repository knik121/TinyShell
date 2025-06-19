#include <unistd.h>
#include "tinyshell.h"

#define is_last_command (I == pipe_count)

bool connect(io pipes[2])
{
    if (pipe_count)
    {
        if (is_last_command || I != 0)
            dup2(pipes[PREVIOUS][READ], STDIN_FILENO);
        if (I == 0 || !is_last_command)
            dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
    }
    return true;
}

void close_(io pipes[2])
{
    if (pipe_count)
    {
        if (is_last_command || I != 0)
            close(pipes[PREVIOUS][READ]);
        if (I == 0 || !is_last_command)
            close(pipes[CURRENT][WRITE]);
    }
}

void alternate(int** pipes)
{
    int* temp = pipes[CURRENT];
    pipes[CURRENT] = pipes[PREVIOUS];
    pipes[PREVIOUS] = temp;
}