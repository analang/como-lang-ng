#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define get_node(x) (((node *)(x))

#include "graph.h"

static void visit(node *, int);

node *create_list(int nchild, int kind, int attrs, char *info, 
  void(*visitor)(node *, int), void(*attribute_visitor)(node *))
{
  node *n = malloc(sizeof(*n));

  n->kind       = kind;
  n->attributes = attrs;
  n->line       = 1;
  n->info = info;
  n->visit           = visitor;
  n->attribute_visit = attribute_visitor;

  n->nchild = nchild;
  n->children = malloc(sizeof(*n) * nchild);

  return n;
}

node *create_root()
{
  return create_list(1, COMO_AST_TOP, 0, "Program", visit, NULL);
}

static void visit_int(node *n, int tabs)
{
  int i;
  for(i = 0; i < tabs; i++)
    fprintf(stdout, " ");

  fprintf(stdout, "Int(%d)\n", ((node_int *)n)->value);
}

static node *create_int(int val)
{
  node_int *n = malloc(sizeof(*n));

  n->base.kind       = COMO_AST_INT;
  n->base.attributes = 0;
  n->base.line       = 1;
  n->base.info       = "Int";
  n->base.nchild     = 0;
  n->base.children   = NULL;
  n->base.visit = visit_int;

  n->value = val;

  return (node *)n;
}

static void visit_id(node *n, int tabs)
{
  int i;
  for(i = 0; i < tabs; i++)
    fprintf(stdout, " ");
  
  fprintf(stdout, "Name(%s)\n", ((node_id *)n)->value);
}

static node *create_id(char *name)
{
  node_id *n = malloc(sizeof(*n));

  n->base.kind       = COMO_AST_ID;
  n->base.attributes = 0;
  n->base.line       = 1;
  n->base.info       = "Name";
  n->base.nchild     = 0;
  n->base.children   = NULL;
  n->base.visit      = visit_id;

  n->value = malloc(strlen(name) + 1);

  memcpy(n->value, name, strlen(name) + 1);

  return (node *)n;
}


static void binop_attribute_visitor(node *n)
{
  fprintf(stdout, "%c", n->attributes);
}

static node *create_binary_op(int op)
{
  return create_list(2, COMO_AST_BINOP, op, "BinaryOp", 
    visit, binop_attribute_visitor);
}

static void add_child(node *n, int index, node *child)
{
  n->children[index] = child;
}

static void visit(node *node, int tabs)
{ 
  int i;
  for(i = 0; i < tabs; i++)
    fprintf(stdout, " ");

  fprintf(stdout, "%s", node->info);
  
  if(node->attribute_visit)
    node->attribute_visit(node);
  fputc('\n', stdout);

  tabs++;

  if(node->nchild)
  {
    for(i = 0; i < node->nchild; i++)
      node->children[i]->visit(node->children[i], tabs);
  }
}

int main(void)
{
  node *root   = create_root(1);
  node *binop  = create_binary_op('+');

  node *assign = create_binary_op('=');
  node *name   = create_id("sum");


  add_child(binop, 0, create_int(26));
  add_child(binop, 1, create_int( 1));

  add_child(assign, 0, name);
  add_child(assign, 1, binop);

  add_child(root, 0, assign);

  visit(root, 0);

  return 0;
}