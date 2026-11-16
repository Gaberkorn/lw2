#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "hash.h"

struct Set
{
    HashTable ht;

    void setInit(Set *s)
    {
        hashInit(&s->ht, 100);
    }

    void setFree(Set *s)
    {
        hashFree(&s->ht);
    }

    void setAdd(Set *s, const std::string &value)
    {
        hashAdd(&s->ht, value, "1");
    }

    void setDel(Set *s, const std::string &value)
    {
        hashDel(&s->ht, value);
    }

    bool setAt(Set *s, const std::string &value)
    {
        return hashContains(&s->ht, value);
    }
};

void executeQuery(Set *s, const std::string &query, bool quiet)
{
    std::stringstream ss(query);
    std::string cmd, name, value;
    ss >> cmd >> name;

    if (cmd == "SETADD")
    {
        ss >> value;
        s->setAdd(s, value);
        if (!quiet)
            std::cout << value << "\n";
    }
    else if (cmd == "SETDEL")
    {
        ss >> value;
        s->setDel(s, value);
        if (!quiet)
            std::cout << value << "\n";
    }
    else if (cmd == "SET_AT")
    {
        ss >> value;
        bool res = s->setAt(s, value);
        if (!quiet)
            std::cout << (res ? "TRUE" : "FALSE") << "\n";
    }
    else if (cmd == "PRINT")
    {
        if (!quiet)
        {
            std::cout << "SET " << name << ":" << "\n";
            hashPrint(&s->ht);
        }
    }
    else
    {
        if (!quiet)
            std::cout << "Unknown command: " << cmd << "\n";
    }
}

void loadFromFile(Set *s, const std::string &filename);
void saveToFile(Set *s, const std::string &filename);

int main(int argc, char **argv)
{
    std::string filename = "";
    std::string query = "";

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc)
        {
            filename = argv[++i];
        }
        else if (arg == "--query" && i + 1 < argc)
        {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty())
    {
        std::cout << "Usage: " << argv[0] << " --file <file> --query '<command>'" << "\n";
        return 1;
    }

    Set s;
    s.setInit(&s);

    loadFromFile(&s, filename);
    executeQuery(&s, query, false);
    saveToFile(&s, filename);

    s.setFree(&s);

    return 0;
}

void loadFromFile(Set *s, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        executeQuery(s, line, true);
    }
    file.close();
}

void saveToFile(Set *s, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return;

    for (int i = 0; i < s->ht.capacity; i++)
    {
        HashNode *cur = s->ht.buckets[i];
        while (cur != nullptr)
        {
            file << "SETADD myset " << cur->key << "\n";
            cur = cur->next;
        }
    }
    file.close();
}