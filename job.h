#pragma once
#include <vector>
#include <string>
#include <sys/types.h>
using namespace std;

struct Job {
    int id;
    pid_t pgid;
    string command;
    bool isRunning;
};

extern vector<Job> job_list;

void add_job(pid_t pgid, const string& command);
void list_jobs();
void bring_to_foreground(int job_id);
void bring_to_background(int job_id);
void remove_job(pid_t pgid);
