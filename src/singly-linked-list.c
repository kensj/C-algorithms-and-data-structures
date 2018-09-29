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

int sll_poll_head() {
	BREAK("POLL HEAD");
	if(head == NULL) {
		warn("%s", "List is empty, returning -1");
		END_BREAK("POLL HEAD");
		return -1;
	}
	if(head->next == NULL) {
		int ret = head->value;
		free(head);
		head = NULL;
		warn("%s", "List is now NULL");
		END_BREAK("POLL HEAD");
		return ret;
	}
	Node* ptr = head;
	head = head->next;
	int ret = ptr->value;
	free(ptr);
	END_BREAK("POLL HEAD");
	return ret;
}

int sll_poll_tail() {
	BREAK("POLL TAIL");
	if(head == NULL) {
		warn("%s", "List is empty, returning -1");
		END_BREAK("POLL TAIL");
		return -1;
	}
	if(head->next == NULL) {
		int ret = head->value;
		free(head);
		head = NULL;
		warn("%s", "List is now NULL");
		END_BREAK("POLL TAIL");
		return ret;
	}

	Node* ptr = head;
	Node* newLast = head;
	while(ptr->next) {
		newLast = ptr;
		ptr = ptr->next;
	}
	int ret = ptr->value;
	debug("Tail value retreived: %d", ret);
	debug("New tail value: %d", newLast->value);
	free(ptr);
	newLast->next = NULL;
	END_BREAK("POLL TAIL");
	return ptr->value;
}

bool sll_contains(int value) {
	BREAK("CONTAINS");
	if(head == NULL) {
		END_BREAK("CONTAINS");
		return false;
	}
	Node* ptr = head;
	while(ptr) {
		if(ptr->value == value) {
			success("Found Value: %d", value);
			END_BREAK("CONTAINS");
			return true;
		}
		ptr = ptr->next;
	}
	warn("Could not find value: %d", value);
	END_BREAK("CONTAINS");
	return false;
}

void sll_print() {
	BREAK("PRINT");
	if(head == NULL) {
		warn("%s", "List is empty, printing nothing");
		END_BREAK("PRINT");
		return;
	}
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

