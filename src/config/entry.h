#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>
#include <string.h>

#define ADDRESS_LENGTH_MAX 256

enum addr_type {
    INV,
    IP,
    UNIX
};

struct stream {
    enum addr_type type;
    char address[ADDRESS_LENGTH_MAX];
    struct stream* next;
};

struct entry {
    enum addr_type type;
    char address[ADDRESS_LENGTH_MAX];
    struct stream* streams;
    struct entry* next;
};

typedef enum addr_type addr_type_t;
typedef struct stream stream_t;
typedef struct entry entry_t;

stream_t* config_stream_init();

void config_stream_destroy(stream_t*);

entry_t* config_entry_init();

void config_entry_destroy(entry_t*);

#endif
