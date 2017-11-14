#include "filestack.h"

filestack_t* config_filestack_init() {
    filestack_t* ret = malloc(sizeof(filestack_t));

    ret->capacity = FILESTACK_DEF_CAPACITY;
    ret->filled = 0;

    ret->arr = malloc(ret->capacity * sizeof(filestate_t*));

    return ret;
}

void config_filestack_push(filestack_t* st, filestate_t* ptr) {
    st->arr[st->filled++] = ptr;

    if(st->filled == st->capacity) { // if full, resize
        int old_cap = st->capacity;
        
        st->capacity += FILESTACK_GROWTH_STEP;
        filestate_t** new = malloc(st->capacity * sizeof(filestate_t*));

        memcpy(new, st->arr, old_cap * sizeof(filestate_t*));

        free(st->arr);
        
        st->arr = new;
    }
}

filestate_t* config_filestack_pop(filestack_t* st) {
    return st->arr[st->filled-- - 1];
}

filestate_t* config_filestack_top(filestack_t* st) {
    return st->arr[st->filled - 1];
}

int config_filestack_contains_name(filestack_t* st, const char* name) {
    for(int i = 0; i < st->filled; i++)
        if(strcmp(st->arr[i]->name, name) == 0)
            return 1;
        

    return 0;
}

void config_filestack_destroy(filestack_t* st) {
    for(int i = 0; i < st->filled; i++) {
        if(st->arr[i])
            config_filestate_destroy(st->arr[i]);
    }

    free(st->arr);
    free(st);
}
