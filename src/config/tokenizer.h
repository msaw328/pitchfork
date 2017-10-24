#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* config_load_content(const char*);

char* config_next_token(char**, int*);

char* config_read_token(char**);

int config_match_token(char**, const char*, int*);

#endif