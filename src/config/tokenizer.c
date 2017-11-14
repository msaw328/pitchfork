#include "tokenizer.h"

const char* WHITESPACE = " \n\t";

char* config_next_token(filestate_t* fs) { // TODO: please make it look normal

    char** s = &(fs->state);
    int* line_count = &(fs->line_count);

    while(strchr(WHITESPACE, (*s)[0]) && (*s)[0] != '\0') {
        if((*s)[0] == '\n') {
            (*line_count)++;
        }
        (*s)++;
    }


    if((*s)[0] == '#') { // comment
        while((*s)[0] != '\n' && (*s)[0] != '\0') {
            (*s)++;
        }
    }
    
    if((*s)[0] == '\0') { // end of file buffer
        (*s) = NULL;
    } else if((*s)[0] == '\n') {
        config_next_token(fs); // jesus christ recursion
    }
    
    return (*s);
}

char* config_read_token(filestate_t* fs) {
    char** s = &(fs->state);

    size_t tok_len = 0;

    while(!strchr(WHITESPACE, (*s)[tok_len]) && (*s)[tok_len] != '\0') {
        tok_len++;
    }

    char* ret = malloc(tok_len + 1);
    strncpy(ret, *s, tok_len);
    ret[tok_len] = '\0';

    *s += tok_len;

    return ret;
}

int config_match_token(filestate_t* fs, const char* token) {
    char** s = &(fs->state);
    int* line_count = &(fs->line_count);

    size_t tok_len = strlen(token);
    if(strncmp(*s, token, tok_len) == 0 && (strchr(WHITESPACE, (*s)[tok_len]) || (*s)[tok_len] == '\0')) {
        *s += tok_len;

        char* tmp = (char*) token;
        while((tmp = strchr(tmp, '\n'))) { // in case someone found it a good idea to put multiple newlines into a token
            (*line_count)++;
            tmp++;
        }

        return 1;
    } else {
        return 0;
    }
}
