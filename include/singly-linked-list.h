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
// Print the entire list
void sll_print();
// Free the entire list
void sll_free();
// Check if list contains
bool sll_contains(int value);