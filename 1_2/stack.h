#ifndef STACK_H
#define STACK_H

#include <string>

struct SNode {
    std::string data;
    SNode* next;
};

struct Stack {
    SNode* head = nullptr;
};

void stackPush(Stack* &s, const std::string &value);
std::string stackPop(Stack* &s);
std::string stackGet(Stack* &s);
#endif