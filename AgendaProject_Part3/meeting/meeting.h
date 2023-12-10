#ifndef AGENDAPROJET_MEETING_H
#define AGENDAPROJET_MEETING_H

#include <stdlib.h>
#include <stdio.h>

#include "../scanString/scanString.h"

typedef struct s_date {
    int day;
    int month;
    int year;
} t_date;

typedef struct s_time {
    int hour;
    int minutes;
} t_time;

typedef struct s_meeting {
    t_date date;
    t_time time;
    t_time length;
    char *subject;
} t_meeting;

typedef struct s_meeting_cell {
    t_meeting meeting;
    struct s_meeting_cell *next;
} t_meeting_cell;

typedef struct s_meeting_list {
    t_meeting_cell *head;
} t_meeting_list;

t_meeting enterMeeting();

t_meeting_cell *createMeetingCell(t_meeting);

t_meeting_list *createEmptyMeetingList();

int isDateBefore(t_meeting, t_meeting);
void insertMeeting(t_meeting, t_meeting_list*);
void removeMeeting(t_meeting_list*);

#endif //AGENDAPROJECT_MEETING_H