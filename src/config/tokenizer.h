#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdlib.h>
#include <string.h>

#include "filestate.h"

char* config_next_token(filestate_t*);

char* config_read_token(filestate_t*);

int config_match_token(filestate_t*, const char*);

#endif