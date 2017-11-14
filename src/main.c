#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config/parser.h"
#include "config/entry.h"
#include "config/filestack.h"
#include "config/filestate.h"

// debug
void print_entry(entry_t*);

int main(int argc, char** argv) {
    filestack_t* fstack = config_filestack_init();

    filestate_t* fs = config_load_file("default.conf");

    config_filestack_push(fstack, fs);


    config_next_token(fs);

    if(!config_match_token(fs, "entry")) {
        //return NULL; // err no entry
        printf("return NULL // err no entry\n");

        printf("error in file %s on line %d\n", fs->name, fs->line_count);
        return 0;
    }

    entry_t* obj = config_parse_entry(fstack);

    if(obj != NULL) {
        print_entry(obj);
        config_entry_destroy(obj);
    }

    fs = config_filestack_top(fstack);

    printf("error in file %s on line %d\n", fs->name, fs->line_count);

    config_filestack_destroy(fstack);
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
