#include "platform.h"
#include "stdlib.h"
#include "levent.h"

// functions dealing with "logical events"

unsigned levent_index_for_name(const char *name) {
    unsigned i;
    // TODO could check for id=-1 or id=0, both show up at end of table ?
    for (i=0; levent_table[i].name; i++) {
        // case insensitive might be better
        if (strcmp(levent_table[i].name,name) == 0) {
            return i;
        }
    }
    return LEVENT_INVALID_INDEX;
}

unsigned levent_index_for_id(unsigned id) {
    unsigned i;
    // TODO could check for id=-1 or id=0, both show up at end of table ?
    for (i=0; levent_table[i].name; i++) {
        // case insensitive might be better
        if (id == levent_table[i].id) {
            return i;
        }
    }
    return LEVENT_INVALID_INDEX;
}

unsigned levent_count(void) {
    static unsigned num_levents = 0;
    if(!num_levents) {
        levent_def *ev;
        // TODO could check for id=-1 or id=0, both show up at end of table ?
        for (ev = levent_table; ev->name; ev++) {
            num_levents++;
        }
    }
    return num_levents;
}

unsigned levent_id_for_name(const char *name) {
    unsigned i = levent_index_for_name(name);
    if (i!=LEVENT_INVALID_INDEX)
        return levent_table[i].id;
    else
        return 0; // or -1 ? both appear at the end of the event list
}

const char * levent_name_for_id(unsigned id) {
    unsigned i = levent_index_for_id(id);
    if (i!=LEVENT_INVALID_INDEX)
        return levent_table[i].name;
    else
        return NULL;
}

// note, slow linear search every time
int levent_post_to_ui_by_name(const char *name) {
    unsigned id=levent_id_for_name(name);
    if(id) {
        PostLogicalEventToUI(id,0);
        return 1;
    }
    return 0;
}

void levent_set_record(void) {
    levent_post_to_ui_by_name("PressRecButton");
    levent_post_to_ui_by_name("UnpressRecButton");
}

void levent_set_play(void) {
    levent_post_to_ui_by_name("PressPBButton");
    levent_post_to_ui_by_name("UnpressPBButton");
}
