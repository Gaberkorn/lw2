#include <iostream>
#include "list.h"

using namespace std;

void listInit(List* list) {
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void listFree(List* list) {
    LNode* cur = list->head;
    while (cur != nullptr) {
        LNode* next = cur->next;
        delete cur;
        cur = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

bool listIsEmpty(List* list) {
    return list->head == nullptr;
}

void listPushTail(List* list, const std::string& value) {
    LNode* node = new LNode{value, list->tail, nullptr};
    if (list->tail != nullptr) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

bool listDelHead(List* list, std::string& out) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return false;
    }
    LNode* old = list->head;
    out = old->data;
    list->head = old->next;
    if (list->head != nullptr) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    delete old;
    list->size--;
    return true;
}

bool listDelByKey(List* list, const std::string& key) {
    if (listIsEmpty(list)) return false;

    std::string prefix = key + ":";
    LNode* cur = list->head;
    
    while (cur != nullptr) {
        if (cur->data.compare(0, prefix.length(), prefix) == 0) {
            if (cur->prev != nullptr) {
                cur->prev->next = cur->next;
            } else {
                list->head = cur->next;
            }
            
            if (cur->next != nullptr) {
                cur->next->prev = cur->prev;
            } else {
                list->tail = cur->prev;
            }
            
            delete cur;
            list->size--;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool listDelValue(List* list, const std::string& value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != value) {
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    } else {
        list->head = cur->next;
    }
    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    } else {
        list->tail = cur->prev;
    }
    delete cur;
    list->size--;
    return true;
}