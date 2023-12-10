cmake_minimum_required(VERSION 3.24)
project(AgendaProject_Part2 C)

set(CMAKE_C_STANDARD 11)

add_executable(AgendaProject_Part2 main.c cell/cell.c cell/cell.h list/list.c list/list.h moduleTimer/timer.c)
