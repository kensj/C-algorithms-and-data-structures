#include "debug.h"
#include <stdbool.h>
#include <math.h>

typedef struct hash_item {
	char* value;
	char* key;
	struct hash_item* next;
} __attribute__ ((__packed__)) hash_item;

typedef struct hash_table {
	u_int size;
	u_int count;
	hash_item** items;
} __attribute__ ((__packed__)) hash_table;

hash_table* new_table();
void ht_put(char* key, char* value);
char* ht_get(char* key);
void ht_remove(char* key);
u_int ht_hash(char* key);
void ht_delete_table();
u_int next_prime();
u_int prev_prime();
void ht_grow_table();
void ht_shrink_table();
bool is_prime(u_int i);

extern u_int prime;
extern hash_table* table;