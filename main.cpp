<<<<<<< HEAD
#include "tinyshell.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

int pipe_count;
int I;
bool is_background;

static void run(char ***commands)
{
    I = -1;
    while (commands[++I])
        if (*commands[I])
            execute(commands[I]);
    while (I-- > 0)
        free_strings(commands[I]);
    free(commands);
}

static bool read_(char **line, const char *prompt)
{
    size_t i = 0, max = 4096;
    int letter;

    std::cout << prompt;
    *line = (char*)malloc(max);
    while ((letter = getchar()) != '\n')
    {
        if (letter == EOF)
            exit(EXIT_SUCCESS);
        if (i == max)
            *line = (char*)realloc(*line, max *= 2);
        (*line)[i++] = letter;
    }
    (*line)[i] = '\0';
    return true;
}

static void check(char *mode, int count, char **arguments)
{
    if (count == 1)
        *mode = INTERACTIVE;
    else if (count == 3 && is_same(arguments[1], "-c"))
        *mode = COMMANDLINE;
    else
        exit_error("check");
}

static void parse_and_run(char *line)
{
    char ***commands;

    is_background = line[strlen(line) - 1] == '&';
    if ((commands = parse(line)))
        run(commands);
}

int main(int count, char **arguments)
{
    char *line;
    char mode;

    check(&mode, count, arguments);
    if (mode == INTERACTIVE)
        while (read_(&line, "tinyshell$ "))
            parse_and_run(line);
    else
        parse_and_run(strdup(arguments[2]));
}
=======
#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
>>>>>>> 8361e7179446ec09d3768c77ef1beb4df89310f4
