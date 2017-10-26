#include "parser.h"

entry_t* config_parse_entry(char** s, int* line_count) {

    entry_t* ret = config_entry_init();

    config_next_token(s, line_count);

    ret->addr_type = config_parse_addr_type(s, line_count);

    if(ret->addr_type == INV_ADDR_TYPE) {
        config_entry_destroy(ret);
        return NULL; // err wrong socket type
    }

    config_next_token(s, line_count);

    if(!config_match_token(s, "{", line_count)) {
        config_entry_destroy(ret);
        return NULL; // err no opening bracket
    }

    int not_done = 1;
    while(not_done) {
        config_next_token(s, line_count);

        if(config_match_token(s, "addr", line_count)) {

            if(ret->addr != NULL) {
                config_entry_destroy(ret);
                return NULL; // err multiple addr declarations
            } else {
                config_next_token(s, line_count);
                ret->addr = config_read_token(s);
            }
        } else if(config_match_token(s, "method", line_count)) {

            if(ret->method != INV_METHOD) {
                config_entry_destroy(ret);
                return NULL; // err multiple method declatarions
            } else {
                ret->method = config_parse_method(s, line_count);
                if(ret->method == INV_METHOD) {
                    config_entry_destroy(ret);
                    return NULL; // err invalid method
                }
            }
        } else if(config_match_token(s, "stream", line_count)) {
            // parse stream
            not_done = 0;
        } else if(config_match_token(s, "}", line_count)) {
            not_done = 0;
        } else {
            config_entry_destroy(ret);
            return NULL; // err invalid token
        }
    }

    return ret;
}

addr_type_t config_parse_addr_type(char** s, int* line_count) {
    addr_type_t ret = INV_ADDR_TYPE;

    config_next_token(s, line_count);

    if(config_match_token(s, "ip", line_count)) {
        ret = IP;
    } else if(config_match_token(s, "unix", line_count)) {
        ret = UNIX;
    }

    return ret;
}

method_t config_parse_method(char** s, int* line_count) {
    method_t ret = INV_METHOD;

    config_next_token(s, line_count);

    if(config_match_token(s, "random", line_count)) {
        ret = RANDOM;
    } else if(config_match_token(s, "order", line_count)) {
        ret = ORDER;
    }

    return ret;
}
