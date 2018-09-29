#include <criterion/criterion.h>
#include "singly-linked-list.h"
/*#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>*/

Node* head;

Test(sf_memsuite, sll_first_value, .fini = sll_free) {
	Node* node = sll_insert(10);
  	cr_assert(node->value == 10, "Value not equal!");
  	cr_assert(node->next == NULL, "List size greater than 1!");
  	cr_assert(head == node, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_three_values, .fini = sll_free) {
	Node* node3 = sll_insert(10);
	Node* node2 = sll_insert(20);
	Node* node1 = sll_insert(30);
  	cr_assert(node1->value == 30, "First value incorrect!");
  	cr_assert(node1->next == node2, "First's next element is not the second!");
  	cr_assert(node2->value == 20, "Second value incorrect!");
  	cr_assert(node2->next == node3, "Second's next element is not the third!");
  	cr_assert(node3->value == 10, "Third value incorrect!");
  	cr_assert(node3->next == NULL, "Third's next element is not null!");
  	cr_assert(head == node1, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_poll_null, .fini = sll_free) {
	int value1 = sll_poll_head();
	int value2 = sll_poll_tail();
	cr_assert(value1 == -1, "Head value is not null!");
	cr_assert(value2 == -1, "Teail value is not null!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_poll_single, .fini = sll_free) {
	sll_insert(10);
	cr_assert(head->value == 10, "Head pointer is incorrect!");
	int value1 = sll_poll_head();
	cr_assert(value1 == 10, "Wrong head value returned!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
	sll_insert(10);
	int value2 = sll_poll_tail();
	cr_assert(head == NULL, "Head pointer is incorrect!");
	cr_assert(value2 == 10, "Wrong tail value returned!");
}

Test(sf_memsuite, sll_poll, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_insert(40);
	cr_assert(head->value == 40, "Head pointer is incorrect!");
	int value1 = sll_poll_head();
	cr_assert(value1 == 40, "Wrong head value returned!");
	int value2 = sll_poll_tail();
	cr_assert(value2 == 10, "Wrong tail value returned!");
}

Test(sf_memsuite, sll_contains_empty, .fini = sll_free) {
	bool contains = sll_contains(10);
	cr_assert(contains == false, "Empty list cannot contain value!");
}

Test(sf_memsuite, sll_contains_single, .fini = sll_free) {
	sll_insert(10);
	bool contains = sll_contains(10);
	cr_assert(contains == true, "List should contain value!");
}

Test(sf_memsuite, sll_contains_first, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	bool contains = sll_contains(30);
	cr_assert(contains == true, "List should contain value!");
}

Test(sf_memsuite, sll_contains_last, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	bool contains = sll_contains(10);
	cr_assert(contains == true, "List should contain value!");
}

Test(sf_memsuite, sll_remove_empty, .fini = sll_free) {
	sll_remove(10);
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_single, .fini = sll_free) {
	sll_insert(10);
	sll_remove(10);
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_middle, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_remove(20);
	sll_print();
	bool contains = sll_contains(20);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head->value == 30, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_first, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_remove(30);
	sll_print();
	bool contains = sll_contains(30);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head->value == 20, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_last, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_remove(10);
	sll_print();
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head->value == 30, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_all_empty, .fini = sll_free) {
	sll_remove_all(10);
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_all_repeating_head, .fini = sll_free) {
	sll_insert(10);
	sll_insert(10);
	sll_insert(10);
	sll_remove_all(10);
	sll_print();
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head == NULL, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_remove_all_middle, .fini = sll_free) {
	sll_insert(20);
	sll_insert(10);
	sll_insert(10);
	sll_insert(10);
	sll_insert(20);
	sll_remove_all(10);
	sll_print();
	bool contains = sll_contains(10);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head->value == 20, "Head pointer is incorrect!");
}


Test(sf_memsuite, sll_remove_all_head_and_tail, .fini = sll_free) {
	sll_insert(20);
	sll_insert(20);
	sll_insert(20);
	sll_insert(10);
	sll_insert(10);
	sll_insert(10);
	sll_insert(20);
	sll_insert(20);
	sll_insert(20);
	sll_remove_all(20);
	sll_print();
	bool contains = sll_contains(20);
	cr_assert(contains == false, "List should not contain value!");
	cr_assert(head->value == 10, "Head pointer is incorrect!");
}

Test(sf_memsuite, sll_get_head_null, .fini = sll_free) {
	int value = sll_get_head();
	cr_assert(value == -1, "List should not contain value!");
}

Test(sf_memsuite, sll_get_head, .fini = sll_free) {
	sll_insert(10);
	int value = sll_get_head();
	cr_assert(value == 10, "List should contain value!");
}

Test(sf_memsuite, sll_get_tail_null, .fini = sll_free) {
	int value = sll_get_tail();
	cr_assert(value == -1, "List should not contain value!");
}


Test(sf_memsuite, sll_get_tail, .fini = sll_free) {
	sll_insert(10);
	int value = sll_get_tail();
	cr_assert(value == 10, "List should contain value!");
}

Test(sf_memsuite, sll_get_tail_many, .fini = sll_free) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_insert(40);
	int value = sll_get_tail();
	cr_assert(value == 10, "List should contain value!");
}
