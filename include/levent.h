#ifndef LEVENT_H
#define LEVENT_H

#define LEVENT_INVALID_INDEX 0xFFFFFFFF

/* logical event definition */
typedef struct {
    char *name; /* name of event, may point to empty string */
    unsigned id; /* event id number used with canon event fuctions (post etc) */
    unsigned param; /* unknown 0-3 */
} levent_def;
/*
table of event definitions in ROM,
address can be found with tools/find_levent
terminated by an event with a NULL (not empty string) name pointer.
*/
extern levent_def levent_table[];

/* return index of named event, or LEVENT_INVALID_INDEX */
unsigned levent_index_for_name(const char *name);

/* return index of event with given id, or LEVENT_INVALID_INDEX */
unsigned levent_index_for_id(unsigned id);

/* number of events in table, including final id 0 and id -1*/
unsigned levent_count(void);

/* return id of named event, or 0 */
unsigned levent_id_for_name(const char *name);

/* return name of event with given id, or NULL */
const char * levent_name_for_id(unsigned id);

/* post the named event with PostLogicalEventToUI */
int levent_post_to_ui_by_name(const char *name);

/* post press/unpress events for RecButton and PBButton */
void levent_set_record(void);
void levent_set_play(void);

#endif
