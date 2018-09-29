#include "singly-linked-list.h"

Node* head;

Node* sll_insert(int value) {
	BREAK("INSERT");
	debug("Inserting value: %d", value);
	Node* newNode = malloc(sizeof(struct Node));
	newNode->value = value;
	if(head == NULL) {
		info("%s", "Setting as first element of list");
		newNode->next = NULL;
	}
	else {
		info("%s", "Pushing to head of list");
		newNode->next = head;
	}
	head = newNode;
	END_BREAK("INSERT");
	return newNode;
}

int sll_poll() {
	return -1;
}

int sll_pop() {
	return -1;
}

void sll_print() {
	BREAK("PRINT");
	printf("%d", head->value);
	Node* ptr = head->next;
	while(ptr) {
		printf(" -> %d", ptr->value);
		ptr = ptr->next;
	}
	printf("\n");
	END_BREAK("PRINT");
}

void sll_free() {
	BREAK("FREE");
	while(head) {
		Node* ptr = head->next;
		debug("Freeing node with value: %d", head->value);
		free(head);
		head = ptr;
	}
	END_BREAK("FREE");
}

