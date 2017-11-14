#ifndef FILESTATE_H
#define FILESTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct filestate {
    char* buff;
    char* state;
    char* name;
    int line_count;
};

typedef struct filestate filestate_t;

filestate_t* config_load_file(const char*);

void config_filestate_destroy(filestate_t*);

#endif
