#ifndef AGENDAPROJET_AGENDA_H
#define AGENDAPROJET_AGENDA_H

#include "time.h"
#include "../contact/contact.h"
#include "../meeting/meeting.h"

typedef struct s_agenda_entry { // Entrée d'agenda
    t_contact *contact;
    t_meeting_list *meetings;
} t_agenda_entry;

typedef struct s_agenda_cell // Cellule de la liste à niveau contenant une entrée d'agenda
{
    t_agenda_entry entry;
    int nbLevels;
    struct s_agenda_cell ** next;
} t_agenda_cell;

typedef struct s_agenda_list { // Liste à niveau de cellules d'entrées d'agenda
    t_agenda_cell ** heads;
} t_agenda_list;

t_agenda_entry *createEntry(t_contact*, t_meeting_list*);

t_agenda_cell *createEmptyCell(t_agenda_entry, int);

t_agenda_list *createEmptyList();

t_agenda_cell *findCell(t_contact *, t_agenda_list*);

void readSpecificLine(const char *filename, int lineNumber, char result[50]);

void fillAgenda(t_agenda_list*);

t_agenda_cell * insertCell(t_agenda_list* , t_agenda_cell*);

t_agenda_cell * isContactInAgenda(t_agenda_list* ,t_contact* );

t_agenda_cell * isContactInAgendaBest(t_agenda_list* ,t_contact* );


#endif //AGENDAPROJET_AGENDA_H
