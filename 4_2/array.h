#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>

struct Array
{
    Array(int value) {
        capacity = (value <= 0) ? 4 : value;
        size = 0;
        data = new std::string[capacity];
    }
    
    std::string *data = nullptr;
    int capacity = 0;
    int size = 0;
};

void arrayPush(Array& a, std::string value);
#endif