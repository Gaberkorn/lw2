#include <iostream>
#include "stack.h"

void stackPush(Stack* &s, const std::string &value)
{
    SNode *newNode = new SNode{value, s->head};
    s->head = newNode;
}

std::string stackPop(Stack* &s)
{
    SNode *newHead = s->head->next;
    std::string returnVal = s->head->data;
    delete s->head;
    s->head = newHead;
    return returnVal;
}

std::string stackGet(Stack* &s)
{
    return s->head->data;
}