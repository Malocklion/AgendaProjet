#include "menu.h"

void showMeetings(t_agenda_list *list) { // Fonction pour afficher les rdv d'un contact

    t_contact *contact = enterContact();
    t_agenda_cell *contactCell = findCell(contact, list);
    if(isContactInAgendaBest(list,contact) == NULL){
        printf("Contact non existant, impossible d'afficher ses rendez-vous.");
        return;
    }

    printf("\n\nRendez-vous du contact %s %s:\n", contact->first_name, contact->last_name);
    t_meeting_cell *temp = contactCell->entry.meetings->head;
    int cpt = 0;

    while (temp != NULL) {
        printf("\nRDV %d :\nle %d/%d/%d - %dh%02d\n", ++cpt, temp->meeting.date.day, temp->meeting.date.month, temp->meeting.date.year, temp->meeting.time.hour, temp->meeting.time.minutes);
        printf("Duree : %d heure(s) et %d minute(s)\nObjet : %s\n", temp->meeting.length.hour, temp->meeting.length.minutes, temp->meeting.subject);
        temp = temp->next;
    }

}

void addMeeting(t_agenda_list *list) { // Fonction pour rajouter un rdv à un contact

    t_contact *contact = enterContact();
    t_agenda_cell *agendaCell = findCell(contact, list);
    insertMeeting(enterMeeting(), (agendaCell->entry.meetings));

}

void deleteMeeting(t_agenda_list *list) {

    t_contact *contact = enterContact();
    t_agenda_cell *agendaCell = findCell(contact, list);
    removeMeeting(agendaCell->entry.meetings);

}


void searchContact(t_agenda_list* list) { // Fonction qui prend les trois premières lettres d'un contact et propose une autocomplétion
    printf("\nEntrez les 3 premieres lettres de la chaine 'nom_prenom' du contact: ");
    char* query = scanString();

    t_agenda_cell *temp = list->heads[3];
    t_agenda_cell *end_limit = NULL; // Va servir à délimiter la zone de recherche

    // On vérifie que la liste n'est pas vide
    if (temp == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    for (int level = 3; level > 0; level--) {
        while (query[3-level] > string_name(*(temp->entry.contact))[3-level]) { // Tant qu'on n'est pas encore arrivé à la bonne lettre, on avance dans la liste
            if ((temp->next[level] == end_limit) || (query[3-level] < string_name(*(temp->next[level]->entry.contact))[3-level])) {
                printf("Aucun contact ne commence par ces lettres.\n");
                return;
            }
            temp = temp->next[level];
        } // On sort de cette boucle uniquement quand la level-ieme lettre du query est la même que celle de l'entrée de temp
        end_limit = temp->next[level];
    }

    printf("Propositions de contact :\n\n");

    while (temp != end_limit) {
        printf("%s %s\n", temp->entry.contact->first_name, temp->entry.contact->last_name);
        temp = temp->next[0];
    }
    return;
}



void startMenu(t_agenda_list * list) { // Pour lancer l'application de gestion d'agenda

    int start = 1;
    int action;
    t_contact * new_contact = NULL;

            printf("Bienvenue dans l'application de gestion d'agenda!\n\n");

    while (start) {

        printf("\nQue puis-je faire pour vous?\n\n");

        printf("1. Ajouter un contact\n");
        printf("2. Afficher les rdv d'un contact\n");
        printf("3. Ajouter un rdv\n");
        printf("4. Supprimer un rdv\n");
        printf("5. Rechercher un contact\n");
        printf("6. Quitter\n\n");

        printf("Veuillez saisir le numero d'une action : ");
        scanf("%d", &action);


        switch (action)
        {
        case 1:
            new_contact = enterContact();
            findCell(new_contact, list);
            break;
        
        case 2:
            showMeetings(list);
            break;

        case 3:
            addMeeting(list);
            break;
        
        case 4:
            deleteMeeting(list);
            break;

        case 5:
            searchContact(list);
            break;
        
        case 6: 
            start = 0;
            break;

        default:
            printf("Saisie non conforme. Reesayez.\n");
            break;
        }
    }

    printf("\nBonne journee!\n");
    free(list);
    list = NULL;
    return;
}

