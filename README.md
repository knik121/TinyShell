# TinyShell

**TinyShell** is a C++ application that emulates a Unix-like command-line shell. It supports key shell functionalities such as program execution, piping, redirection, background jobs, and signal handling, all built from scratch using low-level POSIX system calls.

> 🔧 Built as part of an Operating Systems project to understand process control, job scheduling, and user-kernel interaction in Unix-based environments.

---

## 🚀 Features

- **Program Execution**: Run standard Linux commands using `fork`, `execvp`, and `waitpid`.
- **Input/Output Redirection**: Supports `<` and `>` for redirecting stdin and stdout.
- **Piping**: Connect multiple commands using `|` with proper pipe creation and chaining.
- **Background Execution**: Use `&` to run commands in the background.
- **Job Control**: Implements `jobs`, `fg`, and `bg` using `setpgid`, `tcsetpgrp`, and `kill`.
- **Signal Handling**: Supports `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP) for stopping and interrupting jobs.
- **Command History with Arrow Keys**: Navigate shell history using ↑/↓ via the `readline` library.
- **Modular Codebase**: Includes modular components like `builtin.cpp`, `pipe.cpp`, `job.cpp`, `signal.cpp`, and more.
