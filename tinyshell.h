#pragma once

#include <vector>
#include <string>

#define CHILD 0
#define ERROR -1
#define READ 0
#define WRITE 1
#define CURRENT 1
#define PREVIOUS 0
#define INTERACTIVE 'i'
#define COMMANDLINE 'c'

using io = int[2];

extern int pipe_count;
extern int I;
extern bool is_background;

// Updated to C++ signatures
void execute(const std::vector<std::string>& command);
std::vector<std::vector<std::string>> parse(const std::string& line);

bool connect(io pipes[2]);
void close_(io pipes[2]);
void alternate(int** pipes);

bool redirect_in(std::vector<std::string>& args);
bool redirect_out(std::vector<std::string>& args);

void exit_error(const char* source);
void setup_signals();

// Still C-style (not needed in main.cpp)
void free_strings(char** strings);
void erase_from(std::vector<std::string>& args, size_t count);

