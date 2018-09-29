#include "debug.h"

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
int sll_poll();
// Remove and return tail
int sll_pop();
// Print the entire list
void sll_print();
// Free the entire list
void sll_free();