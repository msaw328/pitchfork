#ifndef READER_H
#define READER_H

#include "parser.h"
#include "entry.h"

struct config {
    entry_t* entries;
    // threads, monitoring etc...
};

typedef struct config config_t;

config_t* config_init();

void config_destroy(config_t*);

#endif
