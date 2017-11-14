#include "parser.h"

entry_t* config_parse_entry(filestack_t* fstack) {
    filestate_t* fs = config_filestack_top(fstack);

    entry_t* ret = config_entry_init();

    config_next_token(fs);

    ret->addr_type = config_parse_addr_type(fs);

    if(ret->addr_type == ADDR_TYPE_INV) {
        config_entry_destroy(ret);
        return NULL; // err wrong socket type
    }

    config_next_token(fs);

    if(!config_match_token(fs, "{")) {
        config_entry_destroy(ret);
        return NULL; // err no opening bracket
    }

    int done = 0;
    while(!done) {

        while(!config_next_token(fs)) { // end of current file, pop from stack
            filestate_t* oldfile = config_filestack_pop(fstack);

            fs = config_filestack_top(fstack);

            config_filestate_destroy(oldfile);
        }


        if(config_match_token(fs, "addr")) {

            if(ret->addr != NULL) {
                config_entry_destroy(ret);
                return NULL; // err multiple addr declarations
            } else {
                config_next_token(fs);
                ret->addr = config_read_token(fs);
            }
        } else if(config_match_token(fs, "method")) {

            if(ret->method != MET_INV) {
                config_entry_destroy(ret);
                return NULL; // err multiple method declarations
            } else {
                ret->method = config_parse_method(fs);
                if(ret->method == MET_INV) {
                    config_entry_destroy(ret);
                    return NULL; // err invalid method
                }
            }
        } else if(config_match_token(fs, "stream")) {
            stream_t* str = config_parse_stream(fstack);
            if(str == NULL) {
                config_entry_destroy(ret);
                return NULL; // error while parsing stream, propagate
            }

            config_stream_append(&(ret->streams), str);

        } else if(config_match_token(fs, "include")) {
            config_next_token(fs);
            char* filename = config_read_token(fs);

            if(config_filestack_contains_name(fstack, filename)) {
                config_entry_destroy(ret);
                free(filename);
                return NULL; // include loop
            }

            filestate_t* newfile = config_load_file(filename);

            config_filestack_push(fstack, newfile);

            fs = newfile;

            free(filename);
        } else if(config_match_token(fs, "}")) {
            done = 1;
        } else {
            config_entry_destroy(ret);
            return NULL; // err invalid token
        }
    }

    return ret;
}

stream_t* config_parse_stream(filestack_t* fstack) {
    filestate_t* fs = config_filestack_top(fstack);

    stream_t* ret = config_stream_init();

    config_next_token(fs);

    ret->addr_type = config_parse_addr_type(fs);

    if(ret->addr_type == ADDR_TYPE_INV) {
        config_stream_destroy(ret);
        return NULL; // err wrong socket type
    }

    config_next_token(fs);

    if(!config_match_token(fs, "{")) {
        config_stream_destroy(ret);
        return NULL; // err no opening bracket
    }

    config_next_token(fs);

    if(!config_match_token(fs, "addr")) {
        config_stream_destroy(ret);
        return NULL; // err wrong token
    }

    config_next_token(fs);

    ret->addr = config_read_token(fs);

    config_next_token(fs);

    if(!config_match_token(fs, "}")) {
        config_stream_destroy(ret);
        return NULL; // err no closing bracket
    }

    return ret;
}

addr_type_t config_parse_addr_type(filestate_t* fs) {

    addr_type_t ret = ADDR_TYPE_INV;

    config_next_token(fs);

    if(config_match_token(fs, "ip")) {
        ret = ADDR_TYPE_IP;
    } else if(config_match_token(fs, "unix")) {
        ret = ADDR_TYPE_UNIX;
    }

    return ret;
}

method_t config_parse_method(filestate_t* fs) {
    method_t ret = MET_INV;

    config_next_token(fs);

    if(config_match_token(fs, "random")) {
        ret = MET_RANDOM;
    } else if(config_match_token(fs, "order")) {
        ret = MET_ORDER;
    }

    return ret;
}
