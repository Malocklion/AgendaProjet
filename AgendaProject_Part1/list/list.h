//
// Created by Malick on 03/12/2023.
//

#ifndef AGENDAPROJECT_PART1_LIST_H
#define AGENDAPROJECT_PART1_LIST_H

#include "../cell/cell.h"

typedef struct s_d_list
{
    int max_levels;
    t_d_cell ** heads;
} t_d_list;

t_d_list * createEmptyList(int);

void addCellToListHead( t_d_list *,t_d_cell * );

void displayLevelListCell ( t_d_list ,int );

void displayListCell ( t_d_list );

void addSortedListCell( t_d_list *, t_d_cell *);


#endif //AGENDAPROJECT_PART1_LIST_H
