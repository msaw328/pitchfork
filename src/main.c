#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config/parser.h"
#include "config/entry.h"

// debug
void print_entry(entry_t* e) {
    printf("ENTRY\n addr type: ");
    char* addr_type = NULL;
    switch(e->addr_type) {
        case INV_ADDR_TYPE:
            addr_type = "INV_ADDR_TYPE";
            break;

        case IP:
            addr_type = "IP";
            break;

        case UNIX:
            addr_type = "UNIX";
            break;
    }
    printf("%s\n", addr_type);
    printf("    addr: %s\n", e->addr);
    char* method = NULL;
    switch(e->method) {
        case INV_METHOD:
            method = "INV_METHOD";
            break;

        case RANDOM:
            method = "RANDOM";
            break;

        case ORDER:
            method = "ORDER";
            break;
    }
    printf("    method: %s\n", method);
}

int main(int argc, char** argv) {
    char* buff = config_load_content("halo.txt");

    char* s = buff;

    int line_count = 1;

    config_next_token(&s, &line_count);

    if(!config_match_token(&s, "entry", &line_count)) {
        //return NULL; // err no entry
        printf("return NULL // err no entry\n");

        printf("line: %d\n", line_count);
        return 0;
    }

    entry_t* obj = config_parse_entry(&s, &line_count);

    if(obj != NULL) {
        print_entry(obj);
        config_entry_destroy(obj);
    }

    printf("line: %d\n", line_count);

    free(buff);
}