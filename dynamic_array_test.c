#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "linear_allocator.h"
#include "dynamic_array.h"

void test_create_array() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	assert(list->data == NULL && list->size == 0 && list->capacity == 0 && list->al == al);
	linear_allocator_free(al);
	free(list);
}

void test_add_element() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);

	int* a;
	*a = 42;
	arraylist_add(list, a, 0);
	assert(list->size == 1 && list->capacity == 8 && *arraylist_get(list, 0) == 42);
	linear_allocator_free(al);
	free(list);
}

void test_add_element_at_index() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	int* a;
	*a = 42;
	arraylist_add(list, a, 0);
	int* b;
	*b = 84;
	arraylist_add(list, b, 1);
	assert(list->size == 2 && list->capacity == 8 && *(int*)arraylist_get(list, 0) == 42 && *(int*)arraylist_get(list, 1) == 84);
	linear_allocator_free(al);
	free(list);
}
void test_add_element_at_invalid_index() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	int* a;
	*a = 42;
	arraylist_add(list, a, 0);
	int* b;
	*b = 84;
	arraylist_add(list, b, 2);
	assert(list->size == 1 && list->capacity == 8 && *(int*)arraylist_get(list, 0) == 42);
	linear_allocator_free(al);
	free(list);
}

void test_add_element_exceeding_capacity() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	for (size_t i = 0; i < 10; i++) {
		int* a = i;
		arraylist_add(list, a, list.size);
	}
	assert(list->size == 10 && list->capacity == 16);
	for (size_t i = 0; i < 10; i++) {
		assert(*arraylist_get(int*)(list, i) == i);
	}
	linear_allocator_free(al);
	free(list);
}

void test_del_middle() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	int* a;
	*a = 42;
	arraylist_add(list, a, 0);
	int* b;
	*b = 84;
	arraylist_add(list, b, 1);
	int* c;
	*c = 126;
	arraylist_add(list, c, 2);
	arraylist_del(list, 1);
	assert(list->size == 2 && list->capacity == 8 && *(int*)arraylist_get(list, 0) == 42 && *(int*)arraylist_get(list, 1) == 126);
	linear_allocator_free(al);
	free(list);
}

void test_add_middle() {
	linear_allocator* al = linear_allocator_init(1024);
	ArrayList* list;
	arraylist_init(list, al);
	int* a;
	*a = 42;
	arraylist_add(list, a, 0);
	int* b;
	*b = 84;
	arraylist_add(list, b, 1);
	int* c;
	*c = 126;
	arraylist_add(list, c, 1);
	assert(list->size == 3 && list->capacity == 8 && *(int*)arraylist_get(list, 0) == 42 && *(int*)arraylist_get(list, 1) == 126 && *(int*)arraylist_get(list, 2) == 84);
	linear_allocator_free(al);
	free(list);
}

int main() {
	test_create_array();
	test_add_element();
	test_add_element_at_index();
	test_add_element_at_invalid_index();
	test_add_element_exceeding_capacity();
	test_del_middle();
	test_add_middle();
	return 0;
}
