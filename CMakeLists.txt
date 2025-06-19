cmake_minimum_required(VERSION 3.31)
project(TinyShell)

set(CMAKE_CXX_STANDARD 20)

add_executable(TinyShell
        main.cpp
        execute.cpp
        parse.cpp
        pipe.cpp
        redirect.cpp
        utility.cpp
        signal.cpp
)
