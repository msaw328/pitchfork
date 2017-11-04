#include "entry.h"

stream_t* config_stream_init() {
    stream_t* ret = malloc(sizeof(stream_t));
    memset(ret, 0, sizeof(stream_t));
    return ret;
}

void config_stream_destroy(stream_t* st) {
    if(st->next) {
        config_stream_destroy(st->next);
    }

    free(st->addr);
    free(st);
}

void config_stream_append(stream_t** head, stream_t* obj) {
    if(*head == NULL) {
        *head = obj;
    } else {
        config_stream_append(&((*head)->next), obj);
    }
}

entry_t* config_entry_init() {
    entry_t* ret = malloc(sizeof(entry_t));
    memset(ret, 0, sizeof(entry_t));
    return ret;
}

void config_entry_destroy(entry_t* en) {
    if(en->next) {
        config_entry_destroy(en->next);
    }

    if(en->streams) {
        config_stream_destroy(en->streams);
    }

    free(en->addr);
    free(en);
}

void config_entry_append(entry_t** head, entry_t* obj) {
    if(*head == NULL) {
        *head = obj;
    } else {
        entry_t* next = (*head)->next;
        config_entry_append(&next, obj);
    }
}
