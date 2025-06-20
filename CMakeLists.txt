cmake_minimum_required(VERSION 3.28.3)
project(TinyShell)

set(CMAKE_CXX_STANDARD 20)

add_executable(TinyShell
        main.cpp
        execute.cpp
        parse.cpp
        pipe.cpp
        redirect.cpp
        utility.cpp
        builtin.cpp
        signal.cpp
        job.cpp
        tinyshell.h
        job.h
)
target_link_libraries(TinyShell readline)
