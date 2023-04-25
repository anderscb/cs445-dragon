#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "semantic.h"
#include "y.tab.h"

/* check that an identifier exists when used */
list_t *semantic_lookup(scope_t *top_scope,list_t *name){
    list_t *p = global_scope_search(top_scope,name);
    if(p == NULL){
        fprintf(stderr, "ERROR: name(%s) used but undeclared\n", name);
    }
    return p;
}

/* set all types in a list of identifiers*/
void semantic_set_type(tree_t *id_list, int type_val){
    if(id_list==NULL) return;

    tree_t *left, *right;
    left = id_list->left;
    right = id_list->right;

    if(left==NULL && right==NULL){
        id_list->attribute.sval->type = type_val;
        fprintf(stderr,"[SET_TYPE: %s, %d]\n", right->attribute.sval->name, right->attribute.sval->type);
    }
    /* set type of right child (ID) */
    else if(right!=NULL){
        right->attribute.sval->type = type_val;
        fprintf(stderr,"[SET_TYPE: %s, %d]\n", right->attribute.sval->name, right->attribute.sval->type);
        semantic_set_type(left, type_val);
    }   
}

/* returns the "type" of a tree */
int type_of(tree_t *t){
    if(t==NULL) return TYPE_ERROR;

    int left_type, right_type;

    switch(t->type){
    case ID:
        return t->attribute.sval->type;
        break;

    case INUM:
        return INTEGRAL;
        break;

    case RNUM:
        return RATIONAL;
        break;

    case ADDOP:
        int left_type = type_of(t->left);
        int right_type = type_of(t->right);
        if(left_type!=right_type){
            fprintf(stderr,"ERROR: type mismatch in ADDOP.\n");
            exit(1);
        }
        return left_type;
        break;

    default:
        break;
    }
}