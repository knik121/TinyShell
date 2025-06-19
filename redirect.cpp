#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "tinyshell.h"

bool redirect_in(std::vector<std::string>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "<" && i + 1 < args.size()) {
            int fd = open(args[i + 1].c_str(), O_RDONLY);
            if (fd < 0) exit_error("open (in)");
            dup2(fd, STDIN_FILENO);
            close(fd);
            erase_from(args, 2);
            return true;
        }
    }
    return true;
}

bool redirect_out(std::vector<std::string>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == ">" && i + 1 < args.size()) {
            int fd = open(args[i + 1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) exit_error("open (out)");
            dup2(fd, STDOUT_FILENO);
            close(fd);
            erase_from(args, 2);
            return true;
        }
    }
    return true;
}
