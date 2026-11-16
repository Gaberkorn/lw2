#ifndef LFU_H
#define LFU_H
#include "hash.h"
#include "list.h"

void lfuSet(std::string &key, std::string &value, int capacity, List &cache, HashTable &map);
void lfuGet(std::string &key, List &cache, HashTable &map, std::string &output);
#endif