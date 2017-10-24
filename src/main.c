#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config/parser.h"
#include "config/entry.h"

int main(int argc, char** argv) {
    char* buff = config_load_content("halo.txt");

    char* token = buff;

    int count = 1;

    entry_t* obj = config_parse_entry(&token, &count);

    if(obj != NULL)
        printf("%d\n", obj->type);

    free(buff);

    free(obj);
    
}