#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config/parser.h"
#include "config/entry.h"

// debug
void print_entry(entry_t*);

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

// debug
void print_entry(entry_t* e) {
    printf("ENTRY addr type: ");
    char* addr_type = NULL;
    switch(e->addr_type) {
        case ADDR_TYPE_INV:
            addr_type = "INV_ADDR_TYPE";
            break;

        case ADDR_TYPE_IP:
            addr_type = "IP";
            break;

        case ADDR_TYPE_UNIX:
            addr_type = "UNIX";
            break;
    }
    printf("%s\n", addr_type);
    printf("    addr: %s\n", e->addr);
    char* method = NULL;
    switch(e->method) {
        case MET_INV:
            method = "INV_METHOD";
            break;

        case MET_RANDOM:
            method = "RANDOM";
            break;

        case MET_ORDER:
            method = "ORDER";
            break;
    }
    printf("    method: %s\n", method);
    printf("    STREAMS:\n");

    stream_t** ite = &(e->streams);
    while(*ite) {
        stream_t* str = *ite;

        printf("        stream addr type: ");
        char* str_addr_type = NULL;
        switch(str->addr_type) {
            case ADDR_TYPE_INV:
                str_addr_type = "INV_ADDR_TYPE";
                break;
    
            case ADDR_TYPE_IP:
                str_addr_type = "IP";
                break;
    
            case ADDR_TYPE_UNIX:
                str_addr_type = "UNIX";
                break;
        }
        printf("%s\n", str_addr_type);
        printf("        stream addr: %s\n\n", str->addr);

        ite = &(str->next);
    }
}
