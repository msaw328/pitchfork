#include "parser.h"

entry_t* config_parse_entry(char** s, int* line_count) {
    entry_t* ret = config_entry_init();

    config_next_token(s, line_count);

    ret->addr_type = config_parse_addr_type(s, line_count);

    if(ret->addr_type == ADDR_TYPE_INV) {
        config_entry_destroy(ret);
        return NULL; // err wrong socket type
    }

    config_next_token(s, line_count);

    if(!config_match_token(s, "{", line_count)) {
        config_entry_destroy(ret);
        return NULL; // err no opening bracket
    }

    int done = 0;
    while(!done) {
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

            if(ret->method != MET_INV) {
                config_entry_destroy(ret);
                return NULL; // err multiple method declarations
            } else {
                ret->method = config_parse_method(s, line_count);
                if(ret->method == MET_INV) {
                    config_entry_destroy(ret);
                    return NULL; // err invalid method
                }
            }
        } else if(config_match_token(s, "stream", line_count)) {
            stream_t* str = config_parse_stream(s, line_count);
            if(str == NULL) {
                return NULL; // error while parsing stream, propagate
            }
            
            config_stream_append(&(ret->streams), str);

        } else if(config_match_token(s, "}", line_count)) {
            done = 1;
        } else {
            config_entry_destroy(ret);
            return NULL; // err invalid token
        }
    }

    return ret;
}

stream_t* config_parse_stream(char** s, int* line_count) {
    stream_t* ret = config_stream_init();

    config_next_token(s, line_count);

    ret->addr_type = config_parse_addr_type(s, line_count);

    if(ret->addr_type == ADDR_TYPE_INV) {
        config_stream_destroy(ret);
        return NULL; // err wrong socket type
    }

    config_next_token(s, line_count);

    if(!config_match_token(s, "{", line_count)) {
        config_stream_destroy(ret);
        return NULL; // err no opening bracket
    }

    config_next_token(s, line_count);

    if(!config_match_token(s, "addr", line_count)) {
        config_stream_destroy(ret);
        return NULL; // err wrong token
    }

    config_next_token(s, line_count);

    ret->addr = config_read_token(s);

    config_next_token(s, line_count);

    if(!config_match_token(s, "}", line_count)) {
        config_stream_destroy(ret);
        return NULL; // err no closing bracket
    }

    return ret;
}

addr_type_t config_parse_addr_type(char** s, int* line_count) {
    addr_type_t ret = ADDR_TYPE_INV;

    config_next_token(s, line_count);

    if(config_match_token(s, "ip", line_count)) {
        ret = ADDR_TYPE_IP;
    } else if(config_match_token(s, "unix", line_count)) {
        ret = ADDR_TYPE_UNIX;
    }

    return ret;
}

method_t config_parse_method(char** s, int* line_count) {
    method_t ret = MET_INV;

    config_next_token(s, line_count);

    if(config_match_token(s, "random", line_count)) {
        ret = MET_RANDOM;
    } else if(config_match_token(s, "order", line_count)) {
        ret = MET_ORDER;
    }

    return ret;
}
