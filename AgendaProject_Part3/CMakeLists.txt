cmake_minimum_required(VERSION 3.24)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c agenda/agenda.c contact/contact.c meeting/meeting.c menu/menu.c scanString/scanString.c complexity/complexity.c complexity/complexity.h timer/timer.c)
