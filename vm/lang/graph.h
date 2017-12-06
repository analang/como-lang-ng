#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>

typedef enum {
  COMO_AST_INT,
  COMO_AST_STRING,
  COMO_AST_DOUBLE,
  COMO_AST_ID,
  COMO_AST_BINOP,
  COMO_AST_TOP  /* Represents the root of the graph */
} node_kind;

typedef uint16_t     node_attributes;
typedef unsigned int node_line;

typedef struct _node {
  node_kind       kind;
  node_attributes attributes;
  node_line       line;
  const char     *info;
  int   nchild;
  struct _node **children;
  void(*attribute_visit)(struct _node *);
  void(*visit)(struct _node *, int);
} node;

/* edge nodes */
typedef struct _node_int {
  node base;
  int value;
} node_int;

typedef struct _node_double {
  node base;
  double value;
} node_double;

typedef struct _node_string {
  node base;
  char *value;
} node_string;

typedef struct _node_id {
  node base;
  char *value;
} node_id;


#endif