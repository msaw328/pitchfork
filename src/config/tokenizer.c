#include "tokenizer.h"

const char* WHITESPACE = " \n\t";

char* config_load_content(const char* name) {
    FILE* f = fopen(name, "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);

    rewind(f);
    
    char* ret = malloc(size + 1);
    fread(ret, 1, (size_t) size, f);

    fclose(f);
    ret[size] = '\0';
    return ret;
}

char* config_next_token(char** s, int* line_count) {
    while(strchr(WHITESPACE, (*s)[0]) && (*s)[0] != '\0') {
        if((*s)[0] == '\n') {
            (*line_count)++;
        }
        (*s)++;
    }

    if((*s)[0] == '\0')
        (*s) = NULL;
    
    return (*s);
}

char* config_read_token(char** s) {
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

int config_match_token(char** s, const char* token, int* line_count) {
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