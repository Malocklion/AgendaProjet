#include <stdio.h>
#include "cell/cell.h"
#include "list/list.h"
#include "time.h"


int main() {
    srand((time(NULL)));


    t_d_list * list = createEmptyList(7);
    t_d_cell * cell = NULL;
    int r = 0;

/*
    for (int i = 0; i < 7; ++i) {
        r = rand() % 7+1;
        cell = createEmptyCell(r,r);
        addCellToListHead(list,cell);
    }
*/


    cell = createEmptyCell(10,6);
    t_d_cell * cell1 = createEmptyCell(7,5);
    t_d_cell * cell2 = createEmptyCell(1,1);
    t_d_cell * cell3 = createEmptyCell(3,2);
    t_d_cell * cell4 = createEmptyCell(8,6);



    addSortedListCell(list,cell);
    addSortedListCell(list,cell2);
    addSortedListCell(list,cell3);


    addCellToListHead(list,cell1);
    addCellToListHead(list,cell4);







    displayListCell(*list);


    free(list->heads);
    list->heads = NULL;

    free(list);
    list = NULL;

    free(cell);
    cell = NULL;
    return 0;
}
