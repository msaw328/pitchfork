#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>

#include "entry.h"
#include "tokenizer.h"

entry_t* config_parse_entry(char** s, int*);

stream_t* config_parse_stream(char** s, int*);

addr_type_t config_parse_addr_type(char** s, int*);

method_t config_parse_method(char**, int*);

#endif
