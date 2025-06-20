#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include "tinyshell.h"

using namespace std;

bool handle_builtin(const vector<string>& args) {
    if (args.empty()) return false;

    if (args[0] == "exit") {
        exit(0);
    }

    if (args[0] == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr)
            cout << cwd << endl;
        else
            perror("pwd failed");
        return true;
    }

    if (args[0] == "cd") {
        const char* path = args.size() > 1 ? args[1].c_str() : getenv("HOME");
        if (chdir(path) != 0)
            perror("cd failed");
        return true;
    }

    return false;  // Not a built-in
}
