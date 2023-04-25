#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "symtab.h"
#include "tree.h"

#define TYPE_ERROR -1

list_t *semantic_lookup(scope_t *, list_t *);
void semantic_set_type(tree_t *, int );
int type_of(tree_t *);

#endif