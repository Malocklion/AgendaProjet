#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "menu/menu.h"
#include "complexity/complexity.h"




int main() {

    t_agenda_list *list = createEmptyList();
    //fillAgenda(list);
    startMenu(list);
    return 0;

}