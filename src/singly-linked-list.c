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
		warn("%s", "List is empty, returning false");
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

void sll_remove(int value) {
	BREAK("REMOVE");
	if(head == NULL) {
		warn("%s", "List is empty, removing nothing");
		END_BREAK("REMOVE");
		return;	
	}
	if(head->value == value) {
		Node* ptr = head;
		head = head->next;
		free(ptr);
		END_BREAK("REMOVE");
		return;	
	}
	Node* ptr = head;
	Node* previous = head;
	while(ptr->next) {
		previous = ptr;
		ptr = ptr->next;
		if(ptr->value == value) {
			debug("Found first occurrence: %d", value);
			debug("Previous value is: %d", previous->value);
			previous->next = ptr->next;
			free(ptr);
			break;
		}
	}
	END_BREAK("REMOVE");
}

void sll_remove_all(int value) {
	BREAK("REMOVE ALL");
	while(head && head->value == value) {
		Node* ptr = head;
		head = head->next;
		free(ptr);
	}

	if(head == NULL) {
		warn("%s", "List is empty, removing nothing");
		END_BREAK("REMOVE ALL");
		return;	
	}

	Node* ptr = head;
	while(ptr) {
		if(ptr->next && ptr->next->value == value) {
			debug("Found occurrence: %d", value);
			debug("Previous value is: %d", ptr->value);
			Node* next_next = ptr->next->next;
			free(ptr->next);
			ptr->next = next_next;
		}
		else ptr = ptr->next;
	}
	END_BREAK("REMOVE ALL");
}

int sll_get_head() {
	BREAK("GET HEAD");
	if(head == NULL) {
		warn("%s", "Head is null, returning -1");
		END_BREAK("GET HEAD");
		return -1;
	}
	success("%s","Value exists");
	END_BREAK("GET HEAD");
	return head->value;
}

int sll_get_tail() {
	BREAK("GET TAIL");
	if(head == NULL) {
		warn("%s", "Head is null, returning -1");
		END_BREAK("GET TAIL");
		return -1;
	}
	Node* ptr = head;
	while(ptr->next) ptr = ptr->next;
	success("%s","Value exists");
	END_BREAK("GET TAIL");
	return ptr->value;
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

