#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/*
 * hash_table.h
 */

#define GROWBY 10

typedef struct item_s {
    char *key;
    int value;
} item;

typedef struct htable_s {
    item **list;
    int capacity;
    int cur_size;
} htable;

int ht_create(htable **ht, int capacity);
int ht_add(htable **ht, char *key, int value);
int ht_lookup(htable **ht, char *key);
void ht_free(htable **ht);

#endif
