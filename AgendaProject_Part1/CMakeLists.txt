cmake_minimum_required(VERSION 3.24)
project(AgendaProject_Part1 C)

set(CMAKE_C_STANDARD 11)

add_executable(AgendaProject_Part1 main.c cell/cell.h cell/cell.c list/list.h list/list.c)
