#include "hash-table.h"
#include <string.h>

u_int prime;
hash_table* table;

hash_table* ht_new_table() {
	BREAK("NEW TABLE");
	hash_table* table = malloc(sizeof(struct hash_table));
	if(prime == 0) prime = 53;
	table->size = prime;
	table->count = 0;
	table->items = calloc(table->size, sizeof(hash_item*));
	success("%s %d", "Successfully created new table of size", prime);
	END_BREAK("NEW TABLE");
	return table;
}

u_int next_prime() {
	u_int i = prime + 2;
	while(!is_prime(i)) i+= 2;
	return i;
}

u_int prev_prime() {
	u_int i = prime - 2;
	while(!is_prime(i)) i-= 2;
	if(i < 53) return 53;
	return i;
}

bool is_prime(u_int i) {
	for(int x=2; x<sqrt(i * 1.0); x++) {
		if(i%x == 0) return false;
	}
	return true;
}

void ht_grow_table() {
	table->items = realloc(table->items, sizeof(hash_item*) * next_prime());
}

void ht_shrink_table() {
	table->items = realloc(table->items, sizeof(hash_item*) * prev_prime());
}

void ht_put(char* key, char* value) {
	BREAK("NEW ITEM");
	if(table == NULL) table = ht_new_table();

	u_int index = ht_hash(key) % table->size;
	if(table->items[index] == NULL) {
		info("%s", "No collision detected, continuing");
		hash_item* i = malloc(sizeof(struct hash_item));
		i->key = strdup(key);
		i->value = strdup(value);
		i->next = NULL;
		table->items[index] = i;
		table->count++;
	}
	else {
		warn("%s", "Collision detected, adding to linked list");
		hash_item* previous = table->items[index];
		hash_item* i = previous;
		while(i != NULL) {
			if(strcmp(i->key, key) == 0) {
				info("%s", "Key already exists, updating");
				free(i->value);
				i->value = strdup(value);
				if(table->count == table->size) ht_grow_table();
				success("Successfully inserted: key=\"%s\" | value=\"%s\"", key, value);
				END_BREAK("NEW ITEM");
				return;
			}
			previous = i;
			i = i->next;
		}
		hash_item* new_item = malloc(sizeof(struct hash_item));
		new_item->key = strdup(key);
		new_item->value = strdup(value);
		new_item->next = NULL;
		previous->next = new_item;
	}
	if(table->count == table->size) ht_grow_table();
	success("Successfully inserted: key=\"%s\" | value=\"%s\"", key, value);
	END_BREAK("NEW ITEM");
}

u_int ht_hash(char* key) {
	BREAK("HASH");
	u_int hash = 5381;
	// djb2 by Dan Bernstein
	while(*key++) hash = ((hash << 5) + hash) + *key;
	debug("Hash index: %d", hash);
	END_BREAK("HASH");
	return hash;
}

char* ht_get(char* key) {
	BREAK("GET ITEM")
	if(table == NULL) {
		warn("%s", "Table is null, returning NULL");
		END_BREAK("GET ITEM");
		return NULL;
	}

	u_int index = ht_hash(key) % table->size;
	hash_item* item = table->items[index];
	while(item) {
		if(strcmp(item->key, key) == 0) {
			info("%s", "Item found, returning");
			END_BREAK("GET ITEM");
			return item->value;
		}
		item = item->next;
	}
	warn("%s", "Item not found");
	return NULL;
}

void ht_remove(char* key) {
	BREAK("DELETE ITEM");
	if(table == NULL) {
		warn("%s", "Table is null, doing nothing");
		END_BREAK("DELETE ITEM");
		return;
	}
	u_int index = ht_hash(key) % table->size;
	hash_item* item = table->items[index];
	hash_item* previous = item;
	while(item) {
		if(strcmp(item->key, key) == 0) {
			info("%s", "Item found, removing");
			if(previous != item) previous->next = item->next;
			else table->items[index] = item->next;
			free(item->key);
			free(item->value);
			free(item);
			break;
		}
		previous = item;
		item = item->next;
	}
	if(table->items[index] == NULL) table->count--;
	//if(table->count < table->size/2) ht_shrink_table();
	success("%s", "Successfully removed item");
	END_BREAK("DELETE ITEM");
}

void ht_delete_table() {
	BREAK("DELETE TABLE");
	for(int i=0; i<table->size; i++) {
		hash_item* item = table->items[i];
		while(item) {
			hash_item* next = item->next;
			free(item->key);
			free(item->value);
			free(item);
			item = next;		
		}
	}
	free(table->items);
	free(table);
	success("%s", "Succesfully deleted table");
	END_BREAK("DELETE TABLE");
}
