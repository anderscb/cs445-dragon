#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"

/* constructor/destructor */
scope_t *make_scope(){
    scope_t *p = (scope_t *)malloc(sizeof(scope_t));
    assert(p != NULL);
    for(int i=0;i<HASH_SIZE;i++){
        p->table[i]=NULL;
    }
    p->next = NULL;
    return p;
}

void free_scope(scope_t *p){
    /* stub: buggy */
    free_list(p->table[HASH_SIZE]);
    free(p);
}

/* stack operations */
scope_t *scope_push(scope_t *top){
    scope_t *p = make_scope();
    if (top!=NULL){
        p->next = top;
    }
    return top;
}

scope_t *scope_pop(scope_t *top){
    if(top != NULL){
        scope_t *tmp = top->next;
        free_scope(top);
        return tmp;
    }
    else{
        return NULL;
    }
}

/* insert at top scope */
list_t *scope_insert(scope_t *top, list_t *name){
    if (top == NULL){
        return NULL;
    }
    int index = hashpjw(name->name);
    list_t *start = top->table[index];
    top->table[index] = list_insert(start,name->name);
    return top->table[index];
}

/* search at top scope */
list_t *scope_search(scope_t *top, list_t *name){
    int index = hashpjw(name->name);

    if (top == NULL){
        return NULL;
    }
    list_t *start = top->table[index];
    return list_search(start,name->name);
}

/* search in all scopes */
list_t *global_scope_search(scope_t *top, list_t *name){
    scope_t *curr = top;
    list_t *p;
    while (curr != NULL){   /* searching all scopes */
        p = scope_search(curr,name);
        if(p!=NULL){    /* found name, return */
            return p;
        }
        curr = curr->next;  /* try next scope */
    }
    return NULL;    /* name not found */
}

/* hashpjw: Peter J. Weinberger's hash function (Dragon book, p 436)
 */

int hashpjw( char *s )
{
  char *p;
  unsigned h = 0, g;

  for( p = s; *p != EOS; p++ )
  {
    h = (h << 4) + (*p);
    if( g = h & 0xf0000000 )
    {
      h = h ^ ( g >> 24 );
      h = h ^ g;
    }
    return h % HASH_SIZE;
  }
}