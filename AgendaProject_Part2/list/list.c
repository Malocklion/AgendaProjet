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

    //On initialise toutes les tetes de la liste a NULL
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

    for(int i = 0 ; i < cell->nbLevels; i++){
        cell->next[i] = levelList->heads[i];
        levelList->heads[i] = cell;
    }
    return;
}


//Fonction qui cree une liste de n niveau avec 2^n -1 cellules de niveau different
t_d_list * createLevelList(int n) {

    //Creation d'une variable avec le nombre de cellules
    int lvl = pow(2, n) - 1;

    //Creation d'un tableau comportant le niveau des cellules a creer
    int* levels = malloc(lvl * sizeof(int));
    //Test de l'allocation
    if(NULL == levels){
        printf("Allocation echoue");
        exit(EXIT_FAILURE);
    }

    //Initialisation des valeurs à zero
    for (int i = 0; i < lvl; i++) {
        levels[i] = 0;
    }

    //On actualise le tableau de niveau des cellules
    for (int i = 2; i < lvl ; i*=2) {
        for (int j = i-1; j < lvl; j=j+i) {
            levels[j]++;
        }
    }


    // Pour que le nbLevel lors de la createCell ne soit pas 0 mais 1 au minimum, car sinon malloc(0) = rien
    for (int i = 0; i < lvl; ++i) {
        levels[i]++;
    }

    //Creation de la liste
    t_d_list* list = createEmptyList(n);

    //On creer les cellules depuis la fin et on les ajoute a l'aide d'une fonction de la partie 1
    for (int i = lvl; i > 0; --i) {
        t_d_cell* newCell = createEmptyCell(i, levels[i - 1]);
        addCellToListHead(list, newCell);
    }

    //On libere l'espace utilise
    free(levels);
    levels = NULL;
    return list;
}





//Fonction de recherche d'une valeur a partir du niveau 0
int isValInLvl0(t_d_list levelList, int val){
    while (levelList.heads[0] != NULL){
        if(val == levelList.heads[0]->value ){
            return 1;
        } else{
            levelList.heads[0] = levelList.heads[0]->next[0];
        }
    }
    return 0;
}



//Recherche a partir du niveau haut en iterative
int isValInList(t_d_list levelList, int val){

    int level = levelList.max_levels - 1;
    t_d_cell * cursor = levelList.heads[level];

    //Boucle jusqu'a qu'on arrive au dernier niveau
    while (level >= 0) {

        //On verifie que le curseur n'est pas nulle et que sa valeur ne soit pas superieure a celle recherche sinon on baisse d'un niveau
        if(NULL == cursor || cursor->value > val){
            if(level-1 > 0){
                cursor = levelList.heads[--level];
            } else{
                return 0 ;
            }
        }

        //On verifie si la valeur de la cellule est celle recherche
        else if(cursor->value == val){
            return 1;
        }

        //On baisse d'un niveau si la prochaine cellule est nulle ou si sa valeur depasse celle recherche
        else if(cursor->next[level] == NULL || cursor->next[level]->value > val){
            level--;
        } else{ //On avance dans la liste
            cursor = cursor->next[level];
        }
    }
    return 0;
}



