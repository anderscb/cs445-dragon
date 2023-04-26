#ifndef LIST_H
#define LIST_H

/* linked list data structure */
typedef struct list_s {
    char *name;     /* identifier name */
    int class;      /* simple variable, function name, procedure, array name */
    int type;       /* INTEGRAL, RATIONAL, ARRAY[LOWER,UPPER]: incomplete */
    /* additional information 
     * FUNC PROC: sequence of expected types (which includes #arguments)
     */
    struct list_s *next;
} list_t;

/* constructor/destructor */
list_t *make_list( char * );
void free_list(list_t *);

void list_print( list_t *);

/* search/insert */
list_t *list_insert( list_t *, char * );
list_t *list_search( list_t *, char * );

#endif