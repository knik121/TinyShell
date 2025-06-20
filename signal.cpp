#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include "tinyshell.h"
#include "job.h"
using namespace std;

extern pid_t fg_pgid;

void handle_sigint(int) {
    // Forward SIGINT (Ctrl+C) to foreground process group
    if (fg_pgid > 0)
        kill(-fg_pgid, SIGINT);
}

void handle_sigtstp(int) {
    // Forward SIGTSTP (Ctrl+Z) to foreground process group
    if (fg_pgid > 0) {
        kill(-fg_pgid, SIGTSTP);
        add_job(fg_pgid, "[Stopped]");  // Minimal stub — you can capture command if you want
        cout << "\n[Job stopped. Use 'bg' or 'fg' to resume]\n";
    }
}

void setup_signal_handlers() {
    signal(SIGINT, handle_sigint);    // Ctrl+C
    signal(SIGTSTP, handle_sigtstp);  // Ctrl+Z
}