#ifndef NODE_H
#define NODE_H

#include "entity_props.h"
#include "vector2.h"

#define NODE_SCALE (DEFAULT_ENTITY_SCALE * 1)

// Usually, will be matched to the container array index.
struct node_id {
    int context;
};

struct node {
    struct node_id id;
    struct vector2 position;
    struct node_id neighbors;
};

#endif// !NODE_H