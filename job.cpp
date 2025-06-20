#include "job.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <algorithm>
#include <sys/wait.h>

using namespace std;

vector<Job> job_list;
static int job_counter = 1;

void add_job(pid_t pgid, const string& command) {
    job_list.push_back({ job_counter++, pgid, command, true });
}

void list_jobs() {
    for (const auto& job : job_list) {
        cout << "[" << job.id << "] " << (job.isRunning ? "Running" : "Stopped")<< " " << job.command <<endl;
    }
}

void bring_to_foreground(int job_id) {
    for (auto& job : job_list) {
        if (job.id == job_id) {
            tcsetpgrp(STDIN_FILENO, job.pgid);
            kill(-job.pgid, SIGCONT);
            int status;
            waitpid(-job.pgid, &status, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            return;
        }
    }
    std::cerr << "fg: job not found\n";
}

void bring_to_background(int job_id) {
    for (auto& job : job_list) {
        if (job.id == job_id) {
            kill(-job.pgid, SIGCONT);
            job.isRunning = true;
            return;
        }
    }
    cerr << "bg: job not found\n";
}

void remove_job(pid_t pgid) {
    job_list.erase(
        remove_if(job_list.begin(), job_list.end(),
                       [pgid](const Job& job) { return job.pgid == pgid; }),
        job_list.end());
}
