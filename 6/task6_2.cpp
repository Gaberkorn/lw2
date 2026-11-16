#include <iostream>
#include <limits>
#include "hash.h"

using namespace std;

enum class AppState
{
    Add = 1,
    Pad,
    Print,
    Exit,
};

string randomString(int length)
{
    string s = "";
    for (int i = 0; i < length; i++)
    {
        s += (char)('a' + rand() % 26);
    }
    return s;
}

int main()
{
    HashTable ht;
    hashInit(&ht, 10);

    bool Exit = false;
    while (!Exit)
    {
        cout << "\n--- MAIN MENU ---\n"
                  << "1. Add element\n"
                  << "2. Padding\n"
                  << "3. Print\n"
                  << "4. Exit\n";
        cout << "Choose option: ";

        int userChoice;
        cin >> userChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(static_cast<AppState>(userChoice))
        {
        case AppState::Add: {
            cout << "Enter key: ";
            string input;
            cin >> input;
            hashAdd(&ht, input, "1");
            break;
        }
        case AppState::Pad: 
            while ((ht.size + 1) * 10 < ht.capacity * 9)
            {
                hashAdd(&ht, randomString(10), randomString(10));
            }
            hashPrint(&ht);
            cout << "Хэш-таблица заполнена почти до 90% от вместимости. \nВведите последнее значение, чтобы произвести реструктуризацию.";
            break;
        
        case AppState::Print: 
            cout << "\nSize: " << ht.size 
            << "\nCap: " << ht.capacity
            << "\n90% от вместимости = " << 0.9 * ht.capacity << " элементов\n";
            hashPrint(&ht);
            break;
        
        case AppState::Exit: 
            cout << "Program closed.\n";
            hashFree(&ht);
            Exit = true;
            break;
        
        default:
            cout << "Error: Unkonwn option!\n";
            break;
        }
    }
    return 0;
}