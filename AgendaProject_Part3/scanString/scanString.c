#include "scanString.h"

char *scanString(void) { // Fonction qui effectue une saisie et qui retourne un 
                         // tableau dynamique stockant les caractères

    fflush(stdin); // On clear le buffer d'entrée

    // On initialise le tableau de caractères de taille 0
    char* inputString = NULL;
    int length = 0;

    // On lit les caractères jusqu'à ce que l'on soit à la fin de la saisie
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        
        // On augmente d'un la taille du tableau pour chaque caractère saisi
        inputString = (char *)realloc(inputString, ++length * sizeof(char));

        if (inputString == NULL) {
            printf("Erreur de réallocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }

        // On stocke le caractère dans le tableau
        inputString[length-1] = (char) c;
    }

    // On ajoute le caractère de fin de chaîne
    inputString = (char *)realloc(inputString, (length+1) * sizeof(char));
    inputString[length] = '\0';

    return inputString;
}