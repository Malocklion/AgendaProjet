//
// Created by Malick on 03/12/2023.
//

#include "list.h"

//Fonction de creation d'une liste de niveau
t_d_list * createEmptyList(int nbNv){

    //On alloue de l'espace pour un tableau de liste
    t_d_list * levelList = malloc(sizeof (t_d_list));

    //On quitte, si l'allocation echoue
    if(NULL == levelList){
        printf("Allocation dynamique echoue");
        exit(EXIT_FAILURE);
    }

    levelList->max_levels = nbNv;

    //On alloue de l'espace pour chaque liste du tableau
    levelList->heads = malloc(nbNv * sizeof (t_d_cell *));
    //On quitte, si l'allocation echoue
    if(NULL == levelList->heads){
        printf("Allocation dynamique echoue");
        exit(EXIT_FAILURE);
    }

    //On initialiste toutes les tetes de la liste a NULL
    for (int i = 0; i < nbNv; ++i) {
        levelList->heads[i] = NULL;
    }
    return levelList;
}


//Fonction pour ajouter des cellules de niveau a partir de la tete de la liste
void addCellToListHead( t_d_list * levelList, t_d_cell * cell ){

    //On verifie si la liste donnee existe
    if(NULL == levelList){
        printf("List do not exist");
        return;
    }

    //On verifie si la cellule donnee existe
    if(NULL == cell){
        printf("Cell do not exist");
        return;
    }

    for(int i = 0 ; i < cell->max_level; i++){
        cell->next[i] = levelList->heads[i];
        levelList->heads[i] = cell;
    }

    return;
}

//Fonction d'affichage d'une liste du tableau
void displayLevelListCell ( t_d_list levelList, int level ){
    //Si le niveau demande est superieur a celui de la liste, alors la liste demande n'existe pas
    if(level > levelList.max_levels){
        printf("List level does not exist");
        return;
    }

    //Creation d'un pointeur afin de comparer les cellules des autres niveau a celui du niveau 0
    t_d_cell * current = levelList.heads[level];
    t_d_cell * level0 = levelList.heads[0];
    printf("[list head_%d @-]--",level);

    //Parours de toute la liste du niveau 0, car elle contient toutes les valeurs
    while(level0!= NULL){
        // Compare si la cellule est la même que celle au niveau 0
        if(current == level0){
            printf(">[%3d|@-]--",current->value);
            current = current->next[level];
        } else{
            printf("-----------");
        }
        level0 = level0->next[0];

    }
    printf(">NULL\n");
    return;
}


//Fonction pour afficher tout le tableau de liste
void displayListCell (t_d_list levelList){

    //On utilise la fonction precedente pour chaque niveau
    for (int i = 0; i < levelList.max_levels; ++i) {
        displayLevelListCell(levelList,i);
    }
    return;
}


//Fonction pour ajouter des cellules dans une liste de facon triee
void addSortedListCell(t_d_list *levelList, t_d_cell *cell) {

    if(levelList == NULL){
        printf("List does not exist");
        return;
    }
    if (cell == NULL) {
        printf("Cell does not exist");
        return;
    }

    for(int i = 0; i<=cell->max_level-1; i++) {
        t_d_cell* temp = levelList->heads[i];
        t_d_cell* prev = NULL;

        // On cherche la bonne position pour l'insertion
        while ( (temp != NULL) && (temp->value < cell->value) ) {
            prev = temp;
            temp = temp->next[i];
        }

        // Insertion de la cellule
        if (prev == NULL) {
            // On l'insere au debut
            cell->next[i] = levelList->heads[i];
            levelList->heads[i] = cell;

        } else {
            // Inserer après la derniere cellule au niveau avec une valeur inferieure
            cell->next[i] = temp;
            prev->next[i] = cell;
        }

    }
    return;
}
