//
// Created by Malick on 03/12/2023.
//

#ifndef AGENDAPROJECT_PART2_CELL_H
#define AGENDAPROJECT_PART2_CELL_H

#include <stdio.h>
#include <stdlib.h>


typedef struct s_d_cell
{
    int value;
    int nbLevels;
    struct s_d_cell ** next;
} t_d_cell;

t_d_cell * createEmptyCell(int, int );
#endif //AGENDAPROJECT_PART2_CELL_H
