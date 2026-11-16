#include "lfu.h"

void lfuSet(std::string &key, std::string &value, int capacity, List &cache, HashTable &map)
{
    std::string dummy;
    if (hashGet(&map, key, dummy))
    {
        listDelByKey(&cache, key);
    }
    else if (cache.size >= capacity)
    {
        LNode *cur = cache.head;
        LNode *trav = nullptr;
        int minFreq = 1000;
        while (cur != nullptr)
        {
            size_t p1 = cur->data.find(':');
            size_t p2 = cur->data.find(':', p1 + 1);
            int f = stoi(cur->data.substr(p2 + 1));
            if (f < minFreq)
            {
                minFreq = f;
                trav = cur;
            }
            cur = cur->next;
        }
        std::string travKey = trav->data.substr(0, trav->data.find(':'));
        listDelValue(&cache, trav->data);
        hashDel(&map, travKey);
    }
    std::string entry = key + ":" + value + ":1";
    listPushTail(&cache, entry);
    hashAdd(&map, key, entry);
}

void lfuGet(std::string &key, List &cache, HashTable &map, std::string &output)
{
    std::string entry;
    if (hashGet(&map, key, entry))
    {
        size_t pos1 = entry.find(':');
        size_t pos2 = entry.find(':', pos1 + 1);

        std::string k = entry.substr(0, pos1);
        std::string v = entry.substr(pos1 + 1, pos2 - pos1 - 1);
        int freq = stoi(entry.substr(pos2 + 1));

        output += v + " ";
        listDelByKey(&cache, k);

        std::string newEntry = k + ":" + v + ":" + std::to_string(freq + 1);
        listPushTail(&cache, newEntry);
        hashAdd(&map, k, newEntry);
    }
    else
    {
        output += "-1 ";
    }
}