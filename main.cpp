#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "tinyshell.h"

using namespace std;

int pipe_count;
int I;
bool is_background;
static vector<string> history;

static void run(vector<vector<string>>& commands) {
    I = -1;
    while (++I < commands.size()) {
        if (!commands[I].empty()) {
            if (handle_builtin(commands[I]))
                continue;  // Don't execvp if built-in handled
            execute(commands[I]);
        }
    }
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
    history.push_back(line);
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
        while (true) {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            string prompt = string("tinyshell:") + cwd + "$ ";
            if (!read_line(line, prompt))
                break;
            parse_and_run(line);
        }
    }
    else
    {
        string cmd(argv[2]);
        parse_and_run(cmd);
    }
    return 0;
}