#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

int getPriority(const std::string &op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|" || op == "^") return 1;
    return 0;
}

void evaluate(Stack* &values, Stack* &ops){
    std::string optr = stackPop(ops);
    std::string a_str = stackPop(values);

    bool ans;
    bool a, b;

    if (a_str == "1") a = true;
    else a = false;

    if (optr == "!") {
        if (a == true)
            ans = false;
        else 
            ans = true;
    }
    else if (optr == "|") {
        std::string b_str = stackPop(values);
        if (b_str == "1") b = true;
            else b = false;
        ans = a | b;
    }
    else if (optr == "&") {
        std::string b_str = stackPop(values);
        if (b_str == "1") b = true;
            else b = false;
        ans = a & b;
    }
    else if (optr == "^") {
        std::string b_str = stackPop(values);
        if (b_str == "1") b = true;
            else b = false;
        ans = a ^ b;
    }

    if (ans == true) stackPush(values, "1");
    else stackPush(values, "0");
}

int main()
{
    Stack *values = new Stack{nullptr};
    Stack *ops = new Stack{nullptr};

    std::string input;
    std::cout << "Enter your logical expression: \n";
    std::getline(std::cin, input);

    for (const auto i : input)
    {
        std::string cur(1, i);

        if (cur == "1" || cur == "0")
            stackPush(values, cur);
        else if (cur == "(")
            stackPush(ops, cur);
        else if (cur == "!" || cur == "&" || cur == "|" || cur == "^")
        {
            while (ops->head != nullptr && getPriority(ops->head->data) >= getPriority(cur))
            {
                if (cur == "!" && ops->head->data == "!")
                    break;
                evaluate(values, ops);
            }
            stackPush(ops, cur);
        }
        else if (cur == ")")
        {
            SNode *currentNode = ops->head;
            while (currentNode->data != "(")
            {
                evaluate(values, ops);
                currentNode = currentNode->next;
            }
            stackPop(ops);
        }
    }

    while (ops->head != nullptr)
        evaluate(values, ops);
    
    std::cout << stackGet(values) << "\n";

    return 0;
}