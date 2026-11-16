#include <iostream>
#include "hash.h"

void increaseSize(HashTable* &ht);

unsigned int hashFunc(const std::string& key, int capacity) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = (hash + c) % capacity;
    }
    return hash;
}

void hashInit(HashTable* ht, int capacity) {
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        ht->buckets[i] = nullptr;
    }
}

void hashFree(HashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != nullptr) {
            HashNode* next = cur->next;
            delete cur;
            cur = next;
        }
    }
    delete[] ht->buckets;
    ht->buckets = nullptr;
    ht->size = 0;
    ht->capacity = 0;
}

void hashAdd(HashTable* ht, const std::string& key, const std::string& value) {
    unsigned int idx = hashFunc(key, ht->capacity);
    HashNode* cur = ht->buckets[idx];

    while (cur != nullptr) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }

    HashNode* newNode = new HashNode{key, value, ht->buckets[idx]};
    ht->buckets[idx] = newNode;
    ht->size++;
    
    if (ht->size * 10 >= ht->capacity * 9)
    {
        increaseSize(ht);
    }
}

bool hashGet(HashTable* ht, const std::string& key, std::string& outValue) {
    unsigned int idx = hashFunc(key, ht->capacity);
    HashNode* cur = ht->buckets[idx];

    while (cur != nullptr) {
        if (cur->key == key) {
            outValue = cur->value;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool hashDel(HashTable* ht, const std::string& key) {
    unsigned int idx = hashFunc(key, ht->capacity);
    HashNode* cur = ht->buckets[idx];
    HashNode* prev = nullptr;

    while (cur != nullptr) {
        if (cur->key == key) {
            if (prev == nullptr) {
                ht->buckets[idx] = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            ht->size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

bool hashContains(HashTable* ht, const std::string& key) {
    std::string dummy;
    return hashGet(ht, key, dummy);
}

void hashPrint(HashTable* ht) {
    for (int i = 0; i < ht->capacity; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != nullptr) {
            std::cout << "[" << cur->key << " " << cur->value << "] ";
            cur = cur->next;
        }
    }
    std::cout << "\n";
}

void increaseSize(HashTable* &ht) {
    HashTable newHt;
    hashInit(&newHt, ht->capacity * 2);

    for (int i = 0; i < ht->capacity; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != nullptr) {
            hashAdd(&newHt, cur->key, cur->value);
            cur = cur->next;
        }
    }

    hashFree(ht);
    *ht = newHt;
    std::cout << "Была произведена реструктуризация хэш-таблицы.\n";
}
