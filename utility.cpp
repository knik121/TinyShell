#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "tinyshell.h"
#include <unistd.h>

using namespace std;

void exit_error(const char* source)
{
    perror(source);
    _exit(EXIT_FAILURE);
}

void free_strings(char** strings)
{
    size_t i = 0;
    while (strings[i])
        free(strings[i++]);
    free(strings);
}

static void pull_back(char** arguments)
{
    size_t i = 0;
    free(arguments[i]);
    do arguments[i] = arguments[i + 1];
    while (arguments[++i]);
}

void erase_from(std::vector<std::string>& args, size_t count) {
    if (count > args.size()) return;
    args.erase(args.begin(), args.begin() + count);
}

