#include "array.h"

void arrayPush(Array& a, std::string value)
{
    a.data[a.size] = value;
    a.size++;
}