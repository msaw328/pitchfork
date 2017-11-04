#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>
#include <string.h>

enum addr_type {
    ADDR_TYPE_INV,
    ADDR_TYPE_IP,
    ADDR_TYPE_UNIX
};

enum method {
    MET_INV,
    MET_RANDOM,
    MET_ORDER
};

struct stream {
    enum addr_type addr_type;
    char* addr;
    struct stream* next;
};

struct entry {
    enum addr_type addr_type;
    enum method method;
    char* addr;
    struct stream* streams;
    struct entry* next;
};

typedef enum addr_type addr_type_t;
typedef enum method method_t;
typedef struct stream stream_t;
typedef struct entry entry_t;

stream_t* config_stream_init();

void config_stream_destroy(stream_t*);

void config_stream_append(stream_t**, stream_t*);

entry_t* config_entry_init();

void config_entry_destroy(entry_t*);

void config_entry_append(entry_t**, entry_t*);

#endif
