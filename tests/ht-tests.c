#include <criterion/criterion.h>
#include "hash-table.h"

Test(sf_memsuite, ht_null, .fini = ht_delete_table) {
	char* value = ht_get("hello");
	cr_assert(value == NULL, "Value should be null!");
}

Test(sf_memsuite, ht_single_value, .fini = ht_delete_table) {
	ht_put("hello", "world");
	char* value = ht_get("hello");
	cr_assert(strcmp(value, "world")==0, "Value incorrect!");
}

Test(sf_memsuite, ht_put_remove, .fini = ht_delete_table) {
	ht_put("hello", "world");
	ht_remove("hello");
	char* value = ht_get("hello");
	cr_assert(value == NULL, "Value should have been removed!");
}

Test(sf_memsuite, ht_put_many, .fini = ht_delete_table) {
	char* value;
	ht_put("hello", "world");
	value = ht_get("hello");
	cr_assert(strcmp(value, "world")==0, "Value incorrect!");
	ht_put("foo", "bar");
	value = ht_get("foo");
	cr_assert(strcmp(value, "bar")==0, "Value incorrect!");
	ht_put("holy", "moly");
	value = ht_get("holy");
	cr_assert(strcmp(value, "moly")==0, "Value incorrect!");
}
