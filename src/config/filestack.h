#ifndef FILESTACK_H
#define FILESTACK_H

#include <string.h>
#include <stdlib.h>

#include "filestate.h"

#define FILESTACK_DEF_CAPACITY 2
#define FILESTACK_GROWTH_STEP 2

struct filestack {
    filestate_t** arr;
    int capacity;
    int filled;
};

typedef struct filestack filestack_t;

filestack_t* config_filestack_init();

void config_filestack_push(filestack_t*, filestate_t*);

filestate_t* config_filestack_pop(filestack_t*);

filestate_t* config_filestack_top(filestack_t*);

void config_filestack_destroy(filestack_t*);

#endif