#include <iostream>
#include <string>
#include "lfu.h"

int main()
{
    int capacity, Q;
    std::cout << "Введите cap и кол-во запросов Q: ";
    if (!(std::cin >> capacity >> Q))
        return 0;

    List cache;
    listInit(&cache);
    HashTable map;
    hashInit(&map, 100);
    std::string output = "";

    for (int i = 0; i < Q; i++)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "SET")
        {
            std::string key, value;
            std::cin >> key >> value;

            lfuSet(key, value, capacity, cache, map);
        }
        else if (cmd == "GET")
        {
            std::string key;
            std::cin >> key;

            lfuGet(key, cache, map, output);
        }
    }
    std::cout << "\n";

    listFree(&cache);
    hashFree(&map);
    std::cout << "Вывод: " << output << "\n";
    return 0;
}