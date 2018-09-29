/*#include <stdio.h>*/
#include <stdlib.h>
#include <string.h>
#include "singly-linked-list.h"

int main(int argc, char *argv[]) {
	sll_insert(10);
	sll_insert(20);
	sll_insert(30);
	sll_print();
	sll_poll_tail();
	sll_print();
	sll_free();
    return EXIT_SUCCESS;
}
