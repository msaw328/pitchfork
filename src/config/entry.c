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

    free(st);
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

    free(en);
}
