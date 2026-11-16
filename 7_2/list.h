#ifndef LIST_H
#define LIST_H
#include <string>

struct LNode {
    std::string data;
    LNode* prev;
    LNode* next;
};

struct List {
    LNode* head;
    LNode* tail;
    int size;
};

void listInit(List* list);
void listFree(List* list);
bool listIsEmpty(List* list);

void listPushHead(List* list, const std::string& value);
void listPushTail(List* list, const std::string& value);
bool listDelHead(List* list, std::string& out);
bool listDelByKey(List* list, const std::string& key);
bool listDelValue(List* list, const std::string& value);
#endif