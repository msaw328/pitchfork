#include "filestate.h"

filestate_t* config_load_file(const char* name) {

    // buff

    FILE* f = fopen(name, "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);

    rewind(f);
    
    char* buff = malloc(size + 1);
    fread(buff, 1, (size_t) size, f);

    fclose(f);
    buff[size] = '\0';

    // name

    int name_len = strlen(name);
    char* name_buff = malloc(name_len + 1);
    name_buff[name_len] = '\0';

    // filestate

    filestate_t* ret = malloc(sizeof(filestate_t));

    ret->buff = buff;
    ret->state = buff;
    ret->name = name_buff;
    ret->line_count = 1;

    return ret;
}

void config_filestate_destroy(filestate_t* fs) {
    free(fs->buff);
    free(fs->name);
    free(fs);
}