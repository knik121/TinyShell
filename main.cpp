#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "tinyshell.h"

using namespace std;

int pipe_count;
int I;
bool is_background;

static void run(vector<vector<string>>& commands)
{
    for (I = 0; I < commands.size(); ++I)
        if (!commands[I].empty())
            execute(commands[I]);
}

static bool read_line(string& line, const string& prompt)
{
    cout << prompt;
    if (!getline(cin, line))
        exit(EXIT_SUCCESS);
    return true;
}

static void check(char& mode, int argc, char** argv)
{
    if (argc == 1)
        mode = INTERACTIVE;
    else if (argc == 3 && string(argv[1]) == "-c")
        mode = COMMANDLINE;
    else
        exit_error("check");
}

static void parse_and_run(string& line)
{
    is_background = !line.empty() && line.back() == '&';
    if (is_background)
        line.pop_back();

    auto commands = parse(line);
    run(commands);
}

int main(int argc, char** argv)
{
    char mode;
    check(mode, argc, argv);

    if (mode == INTERACTIVE)
    {
        string line;
        while (read_line(line, "tinyshell$ "))
            parse_and_run(line);
    }
    else
    {
        string cmd(argv[2]);
        parse_and_run(cmd);
    }
    return 0;
}