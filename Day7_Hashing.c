#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_CAPACITY 20
#define NUMBER_OF_ITEMS 8
#define REHASH_CONSTANT 3 // must be coprime with HASH_TABLE_CAPACITY

typedef struct KeyValuePair {
  int key, value;
} KeyValuePair;

typedef struct HashTableElement {
  int occupied;
  KeyValuePair pair;
} HashTableElement;

typedef struct Node {
  KeyValuePair pair;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

int hash_function_0(int const _key) { return _key % 1000; }
int hash_function_1(int const _key) { return _key % 10; }
int hash_function_2(int const _key) { return _key * 2; }
int (*hash_functions[])(const int) = {hash_function_0, hash_function_1,
                                      hash_function_2};
int rehash(int const _hash) {
  return (_hash + REHASH_CONSTANT) % HASH_TABLE_CAPACITY;
}

HashTableElement *create_linear_hash_table(KeyValuePair const *const _array,
                                           int _hash_function(const int)) {
  HashTableElement *hashTable =
      (HashTableElement *)calloc(HASH_TABLE_CAPACITY, sizeof(HashTableElement));

  for (unsigned index = 0; index < NUMBER_OF_ITEMS; ++index) {
    KeyValuePair const pair = _array[index];

    int hash = _hash_function(pair.key);
    if (hash >= HASH_TABLE_CAPACITY)
      hash = rehash(hash);
    while (hashTable[hash].occupied)
      hash = rehash(hash);

    hashTable[hash].occupied = 1;
    hashTable[hash].pair = pair;
  }
  return hashTable;
}

int find_in_linear_hash_table(HashTableElement const *const _hashTable,
                              int const _key, int _hash_function(const int)) {
  int hash = _hash_function(_key);
  if (hash >= HASH_TABLE_CAPACITY)
    hash = rehash(hash);
  while (_hashTable[hash].occupied && _hashTable[hash].pair.key != _key)
    hash = rehash(hash);

  if (_hashTable[hash].occupied)
    return _hashTable[hash].pair.value;
  return -1;
}

LinkedList *create_chain_hash_table(KeyValuePair const *const _array,
                                    int _hash_function(const int)) {
  LinkedList *const hashTable =
      (LinkedList *)calloc(HASH_TABLE_CAPACITY, sizeof(LinkedList));

  for (unsigned index = 0; index < NUMBER_OF_ITEMS; ++index) {
    KeyValuePair const pair = _array[index];

    int hash = _hash_function(pair.key);
    if (hash >= HASH_TABLE_CAPACITY)
      hash = rehash(hash);

    LinkedList *const list = &hashTable[hash];
    if (list->head == NULL) {
      list->head = (Node *)malloc(sizeof(Node));
      list->head->pair = pair;
      list->head->next = NULL;
    } else {
      Node *tail = list->head;
      while (tail->next != NULL)
        tail = tail->next;
      tail->next = (Node *)malloc(sizeof(Node));
      tail->next->pair = pair;
      tail->next->next = NULL;
    }
  }
  return hashTable;
}

int find_in_chain_hash_table(LinkedList const *const _hashTable, int const _key,
                             int _hash_function(const int)) {
  int hash = _hash_function(_key);
  if (hash >= HASH_TABLE_CAPACITY)
    hash = rehash(hash);

  for (Node *node = _hashTable[hash].head; node != NULL; node = node->next) {
    if (_key == node->pair.key)
      return node->pair.value;
  }
  return -1;
}

int main(void) {
  KeyValuePair array[] = {{1, 5},     {2, 15},     {3, 20}, {4, 7},
                          {1003, 64}, {2002, 500}, {7, 88}, {4001, 250}};

  for (unsigned hashFunctionIndex = 0; hashFunctionIndex < 3;
       ++hashFunctionIndex) {
    HashTableElement const *const hashTable =
        create_linear_hash_table(array, hash_functions[hashFunctionIndex]);

    printf("\nLinear Hash Table using hash function %d Created.\n\n",
           hashFunctionIndex);
    // for (unsigned hashTableIndex = 0; hashTableIndex < HASH_TABLE_CAPACITY;
    // ++hashTableIndex)
    //     printf("{%d,%d} ", hashTable[hashTableIndex].pair.key,
    //     hashTable[hashTableIndex].pair.value);
    // printf("\n");

    int keyToSearch = 0;
    while (1) {
      printf("Enter key to Search (Enter 0 For Next Hash Function): ");
      scanf("%d", &keyToSearch);
      if (!keyToSearch)
        break;

      int const valueFound = find_in_linear_hash_table(
          hashTable, keyToSearch, hash_functions[hashFunctionIndex]);
      if (valueFound == -1)
        printf("Not Found\n");
      else
        printf("Found value = %d\n", valueFound);
    }
  }
  printf("\n");
  for (unsigned hashFunctionIndex = 0; hashFunctionIndex < 3;
       ++hashFunctionIndex) {
    LinkedList const *const hashTable =
        create_chain_hash_table(array, hash_functions[hashFunctionIndex]);

    printf("\nChain Hash Table using hash function %d Created.\n\n",
           hashFunctionIndex);
    // for (unsigned hashTableIndex = 0; hashTableIndex < HASH_TABLE_CAPACITY;
    // ++hashTableIndex)
    // {
    //     for (Node *node = hashTable[hashTableIndex].head; node != NULL; node
    //     = node->next)
    //         printf("{%d,%d}->", node->pair.key, node->pair.value);
    //     printf("X\n");
    // }
    int keyToSearch = 0;
    while (1) {
      printf("Enter key to Search (Enter 0 For Next Hash Function): ");
      scanf("%d", &keyToSearch);
      if (!keyToSearch)
        break;

      int const valueFound = find_in_chain_hash_table(
          hashTable, keyToSearch, hash_functions[hashFunctionIndex]);
      if (valueFound == -1)
        printf("Not Found\n");
      else
        printf("Found value = %d\n", valueFound);
    }
  }

  return 0;
}