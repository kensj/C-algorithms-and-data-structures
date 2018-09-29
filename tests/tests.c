#include <criterion/criterion.h>
#include "singly-linked-list.h"
/*#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>*/

Test(sf_memsuite, First_value, .fini = sll_free) {
	Node* node = sll_insert(10);
  	cr_assert(node->value == 10, "Value not equal!");
  	cr_assert(node->next == NULL, "List size greater than 1!");
}

Test(sf_memsuite, Three_values, .fini = sll_free) {
	Node* node3 = sll_insert(10);
	Node* node2 = sll_insert(20);
	Node* node1 = sll_insert(30);
  	cr_assert(node1->value == 30, "First value incorrect!");
  	cr_assert(node1->next == node2, "First's next element is not the second!");
  	cr_assert(node2->value == 20, "Second value incorrect!");
  	cr_assert(node2->next == node3, "Second's next element is not the third!");
  	cr_assert(node3->value == 10, "Third value incorrect!");
  	cr_assert(node3->next == NULL, "Third's next element is not null!");
}
