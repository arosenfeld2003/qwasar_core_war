#include "hash_table.h"
#include "asm_utils.h"
#include <stdlib.h>

/*
 * hash_table.c
 */

int ht_create(htable **ht, int capacity)
{
    if (((*ht) = (htable*)malloc(sizeof(htable))) == NULL)
        exit(1);
    (*ht)->capacity = (capacity == 0 ? GROWBY : capacity);
    (*ht)->cur_size = 0;
    if (((*ht)->list = (item**)malloc(sizeof(item*) * (*ht)->capacity)) == NULL)
        exit(1);
    return 1;
}

int ht_add(htable **ht, char *key, int value)
{
    int *current = &(*ht)->cur_size;
    int key_len = my_strlen(key);

    /* increase size if full */
    if (*current == (*ht)->capacity) {
        (*ht)->capacity += GROWBY;
        if (((*ht)->list = realloc((*ht)->list, (*ht)->capacity)) == NULL) {
            ht_free(ht);
            exit(1);
        }
    }

    /* create new item */
    if (((*ht)->list[*current] = (item*)malloc(sizeof(item))) == NULL)
        exit(1);

    /* create new key */
    if (((*ht)->list[*current]->key = (char*)malloc(sizeof(char) * key_len + 1)) == NULL)
        exit(1);

    /* copy to key */
    my_strcpy((*ht)->list[*current]->key, key);


    /* store value & increment current */
    (*ht)->list[(*current)++]->value = value;

    return 1;
}

int ht_lookup(htable **ht, char *key)
{
    for (int i = 0; i < (*ht)->cur_size; i++) {
        if (my_strcmp((*ht)->list[i]->key, key) == 0)
            return (*ht)->list[i]->value;
    }
    return -1;
}

void ht_free(htable **ht)
{
    for (int i = 0; i < (*ht)->cur_size; i++) {
        free((*ht)->list[i]->key);      /* free key */
        //free((*ht)->list[i]->value);  /* free value */
        free((*ht)->list[i]);           /* free item */
    }
    free((*ht)->list);                  /* free list */
    free(*ht);                          /* free htable */
}
