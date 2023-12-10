#include "meeting.h"

t_meeting enterMeeting() {
    t_meeting *meeting = malloc(sizeof(t_meeting));
    if (meeting == NULL) {
        printf("Erreur d'allocation dynamique.");
        exit(EXIT_FAILURE);
    }

    printf("Enregistement d'un rdv:\nDate (jj/mm/aaaa):");

    // Vérification de la saisie de la date
    while (scanf("%d/%d/%d", &(meeting->date.day), &(meeting->date.month), &(meeting->date.year)) != 3 || meeting->date.month < 1 || meeting->date.month > 12 || meeting->date.day < 1 || meeting->date.day > 31) {
        printf("Saisie invalide. Veuillez entrer une date au format jj/mm/aaaa : ");
        // Nettoyer le tampon d'entrée
        while (getchar() != '\n');
    }

    printf("Heure du rdv (XXhXX) : ");

    // Vérification de la saisie de l'heure
    while (scanf("%dh%d", &(meeting->time.hour), &(meeting->time.minutes)) != 2 || meeting->time.hour < 0 || meeting->time.hour > 23 || meeting->time.minutes < 0 || meeting->time.minutes > 59) {
        printf("Saisie invalide. Veuillez entrer une heure au format XXhXX : ");
        // Nettoyer le tampon d'entrée
        while (getchar() != '\n');
    }

    printf("Duree du rdv (XXhXX) : ");

    // Vérification de la saisie de la durée
    while (scanf("%dh%d", &(meeting->length.hour), &(meeting->length.minutes)) != 2 || meeting->length.hour < 0 || meeting->length.hour > 23 || meeting->length.minutes < 0 || meeting->length.minutes > 59) {
        printf("Saisie invalide. Veuillez entrer une duree au format XXhXX : ");
        // Nettoyer le tampon d'entrée
        while (getchar() != '\n');
    }

    printf("Objet du rdv : ");
    meeting->subject = scanString();
    return *meeting;
}


t_meeting_cell *createMeetingCell(t_meeting meeting) { // Fonction pour créer une cellule dans la liste de rdv
    t_meeting_cell *newCell = malloc(sizeof(t_meeting_cell));
    if (NULL == newCell) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    newCell->meeting = meeting;
    newCell->next = NULL;
    return newCell;
}

t_meeting_list *createEmptyMeetingList() { // Fonction pour créer une liste vide de rdv
    t_meeting_list *list = malloc(sizeof(t_meeting_list));
    if (NULL == list) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;    
}

int isDateBefore(t_meeting m1, t_meeting m2) { // Fonction qui renvoie 1 si le rdv m1 précède ou est en même temps que le rdv m2
    if (m1.date.year <= m2.date.year) {
        if (m1.date.month <= m2.date.month) {
            if (m1.date.day <= m2.date.day) {
                if (m1.time.hour*100+m1.time.minutes <= m2.time.hour*100+m2.time.minutes) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void insertMeeting(t_meeting meeting, t_meeting_list* meetingList) { // Fonction pour insérer un rdv dans une liste
    t_meeting_cell *meetingCell = createMeetingCell(meeting);
    t_meeting_cell *temp = meetingList->head;

    // On va chercher à mettre le rdv au bon endroit chronologiquement

    // On commence par taiter le cas où l'on doit insérer en tête de liste
    // C'est à dire si la liste est vide ou que notre rdv est avant le premier rdv
    if ((temp == NULL) || isDateBefore(meeting, temp->meeting)) { 
        meetingCell->next = temp;
        meetingList->head = meetingCell;
        return;
    }

    // On traite maintenant tous les autres cas

    while ((temp->next != NULL) && !isDateBefore(meeting, temp->meeting)) {
        temp = temp->next;
    }
    meetingCell->next = temp->next;
    temp->next = meetingCell;
    return;
}


void removeMeeting(t_meeting_list* list) { // Fonction qui permet de suprimer un rdv de la liste;
    int entry_number;
    printf("Quel est le numero du rdv que vous souhaitez supprimer? ");
    scanf("%d", &entry_number);

    t_meeting_cell *temp = list->head;

    // On traite d'abord le cas où la liste ne contient qu'une seule cellule

    if (entry_number == 1 && temp->next == NULL) {
        list->head = NULL;
        free(temp);
    }

    // Puis tous les autres cas

    for (int i=1; i<entry_number; i++) {
        if (temp == NULL) {
            printf("Le rdv numero %d n'existe pas.", entry_number);
            return;
        }
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Le rdv numero %d n'existe pas.", entry_number);
        return;
    }

    t_meeting_cell *oldCell = temp->next;
    temp->next = oldCell->next;
    free(oldCell);

}

