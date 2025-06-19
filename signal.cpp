#include <csignal>
#include <iostream>
using namespace std;

void handle_sigint(int) {
    cout << "\nUse 'exit' to quit.\ntinyshell$ " << flush;
}

void setup_signals() {
    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, SIG_IGN);
}