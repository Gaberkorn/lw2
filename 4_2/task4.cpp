#include <iostream>
#include <string>
#include <sstream>
#include "array.h"

void subarray(Array &a, int targetSum) {
    for (int i = 0; i < a.size; ++i) {
        int currentSum = 0;
        for (int j = i; j < a.size; ++j) {
            currentSum += std::stoi(a.data[j]);
            if (currentSum == targetSum) {
                for (int k = i; k <= j; ++k) {
                    std::cout << a.data[k] << " ";
                }
                std::cout << "\n";
            }
        }
    }
}

int main(){
    size_t arraySize;
    std::cout << "Enter array's capacity: ";
    std::cin >> arraySize;

    Array a(arraySize);

    for (size_t i = 0; i < arraySize; ++i){
        std::string input;
        std::cin >> input;
        try {
            std::stoi(input);
        }
        catch(...)
        {
            std::cerr << "Element " << input << " is not an integer. Program terminated!\n";
            return 1;
        }
        arrayPush(a, input);
    }

    int targetSum;
    std::cout << "Enter array's target sum: ";
    std::cin >> targetSum;

    subarray(a, targetSum);

    return 0;
}