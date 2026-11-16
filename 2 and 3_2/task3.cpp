#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "hash.h"

struct Set
{
    HashTable ht;

    void setInit(Set *s) { hashInit(&s->ht, 100); }
    void setFree(Set *s) { hashFree(&s->ht); }
    void setAdd(Set *s, const std::string &value) { hashAdd(&s->ht, value, "1"); }
    void setDel(Set *s, const std::string &value) { hashDel(&s->ht, value); }
    bool setAt(Set *s, const std::string &value) { return hashContains(&s->ht, value); }
};

std::vector<int> setToVector(const Set &s)
{
    std::vector<int> elements;
    for (int i = 0; i < s.ht.capacity; i++)
    {
        HashNode *cur = s.ht.buckets[i];
        while (cur != nullptr)
        {
            elements.push_back(std::stoi(cur->key));
            cur = cur->next;
        }
    }
    return elements;
}

int main()
{
    std::string input;
    std::cout << "S = ";
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string value;

    Set S, S1, S2, reachableSums;
    S.setInit(&S);
    S1.setInit(&S1);
    S2.setInit(&S2);
    reachableSums.setInit(&reachableSums);

    while (ss >> value)
    {
        try
        {
            std::stoi(value);
        }
        catch (...)
        {
            std::cerr << "Element " << value << " is not an integer. Program terminated!\n";
            exit(1);
        }
        S.setAdd(&S, value);
    }

    std::vector<int> nums = setToVector(S);
    int totalSum = 0;
    for (int x : nums)
        totalSum += x;
    int target = totalSum / 2;

    std::vector<int> parent(target + 1, -1);
    reachableSums.setAdd(&reachableSums, "0");
    parent[0] = 0;

    for (int num : nums)
    {
        for (int s = target; s >= num; s--)
        {
            if (reachableSums.setAt(&reachableSums, std::to_string(s - num)) &&
                !reachableSums.setAt(&reachableSums, std::to_string(s)))
            {
                reachableSums.setAdd(&reachableSums, std::to_string(s));
                parent[s] = num;
            }
        }
    }

    int bestSum = 0;
    for (int s = target; s >= 0; s--)
    {
        if (reachableSums.setAt(&reachableSums, std::to_string(s)))
        {
            bestSum = s;
            break;
        }
    }

    int currSum = bestSum;
    while (currSum > 0)
    {
        int val = parent[currSum];
        S1.setAdd(&S1, std::to_string(val));
        currSum -= val;
    }

    for (int x : nums)
    {
        std::string key = std::to_string(x);
        if (!S1.setAt(&S1, key))
        {
            S2.setAdd(&S2, key);
        }
    }

    std::cout << "Subset 1: ";
    hashPrint(&S1.ht);

    std::cout << "Subset 2: ";
    hashPrint(&S2.ht);

    int diff = std::abs((totalSum - bestSum) - bestSum);
    std::cout << "Min sum difference: " << diff << "\n";

    S.setFree(&S);
    S1.setFree(&S1);
    S2.setFree(&S2);
    reachableSums.setFree(&reachableSums);

    return 0;
}
