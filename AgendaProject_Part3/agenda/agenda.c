#include "agenda.h"

t_agenda_entry *createEntry(t_contact* contact, t_meeting_list* meetings) {
    t_agenda_entry *entry = malloc(sizeof(t_agenda_entry));
    if (NULL == entry) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    entry->contact = contact;
    entry->meetings = meetings;
    return entry;
}

t_agenda_cell * createEmptyCell(t_agenda_entry entry, int levelNb){ // Fonction pour créer une cellule vide
    // On alloue de la mémoire pour cette cellule
    t_agenda_cell * newCell = malloc(sizeof(t_agenda_cell));
    if (NULL == newCell) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // On l'initialise (ATTENTION : On veut levelNb niveau mais il faut pouvoir accéder aux next des autres dans la fonction insert, sinon segfault car l'emplacement mémoire n'est pas défini)
    newCell->nbLevels = levelNb;
    newCell->entry = entry;

    // On alloue de la mémoire pour son tableau de pointeurs
    newCell->next = malloc(4 * sizeof (t_agenda_cell*));
    
    if ((NULL == newCell->next) && (levelNb != 0)) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    
    // Et on les met tous à NULL
    for(int i = 0; i < 4;i++){
        newCell->next[i] = NULL;
    }
    
    return newCell;
}

t_agenda_list * createEmptyList() {

    int nbNv = 4; // Dans le cas présenté par les consignes, on utilise une liste à 4 niveaux

    // On alloue de l'espace mémoire pour la liste
    t_agenda_list *agenda = malloc(sizeof(t_agenda_list));

    if(NULL == agenda){
        printf("Erreur d'allocation dynamique");
        exit(EXIT_FAILURE);
    }

    // On alloue de l'espace pour chaque pointeur du tableau
    agenda->heads = malloc(nbNv * sizeof(t_agenda_cell *));

    if(NULL == agenda->heads){
        printf("Erreur d'allocation dynamique");
        exit(EXIT_FAILURE);
    }

    // On initialiste toutes les tetes de la liste a NULL
    for (int i = 0; i < nbNv; ++i) {
        agenda->heads[i] = NULL;
    }

    return agenda;
}








// Fonction pour lire une ligne spécifique depuis un fichier
void readSpecificLine(const char *filename, int lineNumber, char result[50]) { // 50 étant arbitrairement la longueur maximale d'un prénom ou nom en caractères
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("For %s\n", filename);
        perror("Erreur lors de l'ouverture du fichier ");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lineNumber; ++i) {
        if (fgets(result, 50, file) == NULL) {
            fprintf(stderr, "Erreur de lecture de la ligne %d.\n", lineNumber);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        result[strcspn(result, "\n")] = '\0';
    }

    fclose(file);
}

void fillAgenda(t_agenda_list *list) {

    srand((unsigned int)time(NULL));

    for (int cpt = 0; cpt<20; cpt++) {

        long rand_f = (long) rand() % 36047;
        long rand_l = (long) (rand() * rand()) % 218982;

        t_contact *contact = malloc(sizeof(contact));
        if (NULL == contact) {
            printf("Erreur d'allocation dynamique");
            exit(EXIT_FAILURE);
        }

        char randomFirstName[50];
        char randomLastName[50];

        readSpecificLine("../nat2021.csv", rand_f, randomFirstName);
        readSpecificLine("../noms2008nat_txt.txt", rand_l, randomLastName);

        contact->first_name = randomFirstName;
        contact->last_name = randomLastName;
        findCell(contact, list);

    }
}



t_agenda_cell * insertCell(t_agenda_list * agenda,t_agenda_cell * new_cell) {

    char *current_contact_name = string_name(*new_cell->entry.contact);

    if (agenda->heads[0] == NULL) {
        for (int i = 0; i < 4; ++i) {
            agenda->heads[i] = new_cell;
        }
    } else if (strcasecmp(agenda->heads[0]->entry.contact->last_name, new_cell->entry.contact->last_name) < 0) {
        for (int k = 0; k <= 3; ++k) {
            new_cell->next[k] = agenda->heads[k];
            agenda->heads[k] = new_cell;
        }
    } else {

        //Boucle pour l'insertion
        for (int i = 0; i < 4; ++i) {


            t_agenda_cell *tmp = agenda->heads[i];
            t_agenda_cell *prev = NULL;

            while ((tmp != NULL) &&
                   strcasecmp(tmp->entry.contact->last_name, new_cell->entry.contact->last_name) < 0) {
                prev = tmp;
                tmp = tmp->next[i];
            }
            //On lie la première cellule
            if (i == 0) {
                prev->next[i] = new_cell;
                new_cell->next[i] = tmp;
            }

            if (i == 1) {
                //On vérifie si les troisièmes lettres et celles précédentes(car pas d'intêret si celle avant ne le sont pas) sont égaux
                if (!(prev->entry.contact->last_name[0] == current_contact_name[0] &&
                      prev->entry.contact->last_name[1] == current_contact_name[1]
                      && prev->entry.contact->last_name[2] == current_contact_name[2])) {
                    prev->next[i] = new_cell;
                    new_cell->next[i] = tmp;
                }
            }

            if (i == 2) {
                //On vérifie si les deuxièmes lettres et celles précédantes sont égaux
                if (!(prev->entry.contact->last_name[0] == current_contact_name[0] &&
                      prev->entry.contact->last_name[1] == current_contact_name[1])) {
                    prev->next[i] = new_cell;
                    new_cell->next[i] = tmp;
                }
            }

            if (i == 3) {
                //On vérifie si les premières lettres sont égaux
                if (prev->entry.contact->last_name[0] != current_contact_name[0]) {
                    prev->next[i] = new_cell;
                    new_cell->next[i] = tmp;
                }
            }
        }





        //Cette fois ci on la lie correctement à la cellule d'après
        for (int j = 0; j < 4; j++) {

            if (new_cell->next[j] == NULL) {
                break;
            } else {
                char * next_name = string_name(*new_cell->next[j]->entry.contact);
                if (j == 1 && strcmp(current_contact_name, next_name) == 0) {
                    new_cell->next[j] = new_cell->next[j]->next[j];
                }

                if (j == 2 && strncmp(current_contact_name, next_name, 2) == 0) {
                    new_cell->next[j] = new_cell->next[j]->next[j];
                }

                if (j == 3 && current_contact_name[0] == next_name[0]) {
                    new_cell->next[j] = new_cell->next[j]->next[j];
                }
            }
            printf("\n");
        }
    }
    return new_cell;
}


t_agenda_cell *findCell(t_contact *contact, t_agenda_list *agenda) {
    if(isContactInAgendaBest(agenda,contact) == NULL){
        t_agenda_entry * entry = createEntry(contact,createEmptyMeetingList());
        t_agenda_cell  * new_cell = createEmptyCell(*entry,4);
        return insertCell(agenda,new_cell);
    } else{
        return isContactInAgendaBest(agenda,contact);
    }
}



t_agenda_cell * isContactInAgenda(t_agenda_list * agenda,t_contact * contact){
   if(NULL == agenda){
       exit(EXIT_FAILURE);
   }

   t_agenda_cell * tmp = agenda->heads[0];
   t_agenda_cell * prev = NULL;

    while (tmp!= NULL){
        if(strcasecmp(tmp->entry.contact->last_name,contact->last_name) == 0 && strcasecmp(tmp->entry.contact->first_name,contact->first_name) == 0){
            return tmp;
        }
        prev = tmp;
        tmp = tmp->next[0];
    }

    return NULL;

}


t_agenda_cell * isContactInAgendaBest (t_agenda_list * agenda, t_contact* contact){
    if(NULL == agenda || NULL == contact){
        printf("paramètres rentrées non existant");
        exit(EXIT_FAILURE);
    }
    int level = 3;
    t_agenda_cell * cursor = agenda->heads[level];

    while(level >= 0){
        if(NULL == cursor){
            if(level == 0){
                return NULL;
            }else{
                level--;
                cursor = agenda->heads[level];
            }
        }else if(strcasecmp(cursor->entry.contact->last_name,contact->last_name) == 0 && strcasecmp(cursor->entry.contact->first_name,contact->first_name) == 0){
                return cursor;

        } else if(cursor->next[level] == NULL || strcasecmp(cursor->entry.contact->last_name,contact->last_name) > 0){
            level--;
        } else{
            cursor = cursor->next[level];
        }
    }
    return NULL;
}






