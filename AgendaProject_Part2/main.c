#include <stdio.h>
#include "list/list.h"
#include "cell/cell.h"
#include "moduleTimer/timer.h"

int main() {
    t_d_list * levelList;
    int n = 0;
    int r = 0;
    int cpt = 7;

    srand((time(NULL)));

    while(cpt < 25) {
        printf("%d", cpt);
        levelList = createLevelList(cpt);
        n =pow(2,cpt)-1;

        startTimer();
        for (int j = 0; j < 10000; ++j) {
            r = rand() % n;
            isValInLvl0(*levelList,r);
        }
        stopTimer();
        displayTime();


        startTimer();
        for (int l = 0; l < 10000; ++l) {
            r = rand() % n;
            isValInList(*levelList,r);
        }
        stopTimer();
        displayTime();

        cpt++;
        printf("\n");

    }

    free(levelList->heads);
    free(levelList);
    return 0;
}
