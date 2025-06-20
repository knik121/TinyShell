#include <csignal>
#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void handle_sigint(int signum) {
    cout << "\nCaught Ctrl+C (SIGINT). Type 'exit' to quit."<<endl;
    cout << "tinyshell$ " <<flush;
}

void setup_signal_handlers() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);
}