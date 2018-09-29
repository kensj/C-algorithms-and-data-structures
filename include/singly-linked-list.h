#include "debug.h"
#include <stdbool.h>

// Store our node
typedef struct Node {
	struct Node* next;
	int value;
} __attribute__ ((__packed__)) Node;

// Store our head
extern Node* head;

// Insert value and return node 
Node* sll_insert(int value);
// Remove and return head
int sll_poll_head();
// Remove and return tail
int sll_poll_tail();
// Get first element
int sll_get_head();
// Get last element
int sll_get_tail();
// Remove first occurrence of value
void sll_remove(int value);
// Remove all occurrences of value
void sll_remove_all(int value);
// Print the entire list
void sll_print();
// Free the entire list
void sll_free();
// Check if list contains
bool sll_contains(int value);