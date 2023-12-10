#include "contact.h"

t_contact *enterContact() { // Permet d'entrer un contact
    t_contact *contact = malloc(sizeof(t_contact));
    if (NULL == contact) {
        printf("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    printf("\nEntrez le prenom du contact: ");
    contact->first_name = scanString();
    printf("Entrez le nom de famille du contact: ");
    contact->last_name = scanString();
    return contact;
}


char* string_name(t_contact contact) { // Donne la chaine 'nom_prenom' correspondante à un contact
    
    // Vérification des pointeurs pour éviter les erreurs de segmentation
    if (contact.first_name == NULL || contact.last_name == NULL) {
        return NULL;
    }    

    // Calcul de la taille de la chaine résultante
    int length = strlen(contact.first_name) + strlen(contact.last_name) + 2; // +2 pour le _ et le \0

    // Allocation de la mémoire
    char* string = malloc(length*sizeof(char));
    if (NULL == string) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // Construction de la chaîne résultante en minuscules
    for (size_t i = 0; contact.last_name[i] != '\0'; i++) {
        string[i] = tolower(contact.last_name[i]);
    }
    
    string[strlen(contact.last_name)] = '_';

    for (size_t i = 0; contact.first_name[i] != '\0'; i++) {
        string[strlen(contact.last_name) + 1 + i] = tolower(contact.first_name[i]);
    }
    
    string[length - 1] = '\0';
    
    return string;
}

