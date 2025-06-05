#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "pool_allocator.h"
#include "stddef.h"

typedef struct bucket bucket;

typedef struct {
	void* data;
	char* key;
	bucket* next;
} bucket;

typedef struct {
	bucket** buckets;
	pool_allocator* pl;
	size_t capacity;
} HashTable;


int hashfunction(const char* key, size_t size);
void hashtable_init(HashTable* ht, size_t capacity, pool_allocator* pl);
void hashtable_insert(HashTable* ht, const char* key, void* value);
void* hashtable_get(HashTable* ht, const char* key);
void hashtable_del(HashTable* ht, const char* key);
void hashtable_free(HashTable* ht);

#endif
