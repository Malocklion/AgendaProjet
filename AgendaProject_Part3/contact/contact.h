#ifndef AGENDAPROJET_CONTACT_H
#define AGENDAPROJET_CONTACT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pour strlen()
#include <ctype.h> // Pour tolower()
#include "../scanString/scanString.h"


typedef struct s_contact{
    char *first_name;
    char *last_name;
} t_contact;

t_contact *enterContact();
char* string_name(t_contact);


#endif //AGENDAPROJECT_CONTACT_H