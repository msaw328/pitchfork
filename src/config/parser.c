#include "parser.h"

entry_t* config_parse_entry(char** s, int* line_count) {

    config_next_token(s, line_count);

    if(!config_match_token(s, "entry", line_count)) {
        return NULL; // err
    }

    entry_t* ret = config_entry_init();

    config_next_token(s, line_count);

    ret->type = config_parse_addr_type(s, line_count);

    if(ret->type == INV) {
        free(ret);
        return NULL; // err
    }

    config_next_token(s, line_count);

    if(!config_match_token(s, "{", line_count)) {
        free(ret);
        return NULL; // err
    }

    int not_done = 1;
    while(not_done) {
        config_next_token(s, line_count);

        char* addr = NULL;

        stream_t* 

        if()

        
    }



    return ret;
}

addr_type_t config_parse_addr_type(char** s, int* line_count) {
    addr_type_t ret = INV;

    if(config_match_token(s, "ip", line_count)) {
        ret = IP;
    } else if(config_match_token(s, "unix", line_count)) {
        ret = UNIX;
    }

    return ret;
}

char* config_parse_addr(char** s, int* line_count) {
    char* ret = NULL;

    if(config_match_token(s, "addr", line_count)) {
        config_next_token(s, line_count);

        ret = config_read_token(s);
    }

    return ret;
}
