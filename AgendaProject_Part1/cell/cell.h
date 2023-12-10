//
// Created by Malick on 03/12/2023.
//

#ifndef AGENDAPROJECT_PART1_CELL_H
#define AGENDAPROJECT_PART1_CELL_H

#include <stdio.h>
#include <stdlib.h>


typedef struct s_d_cell
{
    int value;
    int max_level;
    struct s_d_cell ** next;
} t_d_cell;

t_d_cell * createEmptyCell(int, int );

#endif //AGENDAPROJECT_PART1_CELL_H
