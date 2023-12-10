//
// Created by Malick on 10/12/2023.
//

#include "complexity.h"


void ComparaisonComplexity(t_agenda_list * list){
    t_agenda_list * levelList;
    int n = 0;
    int cpt = 7;

    srand((time(NULL)));

    while(cpt < 25) {
        printf("%d", cpt);
        //On choisit un contact aléatoirement qu'on recherchera
        t_contact * contact = enterContact();
        //On crée la liste en incluant tous les noms

        startTimer();
        for (int j = 0; j < 10000; ++j) {
            isContactInAgenda(levelList,contact);
        }
        stopTimer();
        displayTime();


        startTimer();
        for (int l = 0; l < 10000; ++l) {
            isContactInAgendaBest(levelList,contact);
        }
        stopTimer();
        displayTime();

        cpt++;
        printf("\n");

    }

    free(levelList->heads);
    free(levelList);
    return;
}



