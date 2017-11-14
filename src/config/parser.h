#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>

#include "entry.h"
#include "tokenizer.h"
#include "filestack.h"

entry_t* config_parse_entry(filestack_t*);

stream_t* config_parse_stream(filestack_t*);

addr_type_t config_parse_addr_type(filestate_t*);

method_t config_parse_method(filestate_t*);

#endif
