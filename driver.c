#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "symtab.h"

#define MAX_LEN 32

main(){
    int choice;
    scope_t *top = NULL;
    list_t *top = NULL;
    char buffer[MAX_LEN];

    while (1){
        printf( "0.insert 1.search 2.show\n");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            printf("name = ");
            scanf("%s",buffer);
            top = list_insert(top,buffer);
            break;
        case 1:
            printf("search name = ");
            scanf("%s",buffer);
            list_t *p = list_search(top,buffer);
            if (p != NULL) {
                printf("Found[%s] not found\n", buffer);
            }
            else{
                printf("Name[%s] not found\n",buffer);
            }
            break;
        case 2:
            list_print(top);
            break;
        default:
            printf("Error option: %d\n",choice);
        }
    }
}