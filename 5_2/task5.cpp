#include <iostream>
#include <sstream>

#include "AVL.h"

bool isStreamFailed(const std::stringstream &ss)
{
    if (ss.fail())
    {
        std::cout << "Error: Invalid command format!\n";
        return true;
    }
    return false;
}

int main()
{
AVLTree myAVL;
    std::string line;

    std::cout << "\n--- COMMANDS ---\n"
              << "TINSERT <integer>\n"
              << "TSEARCH <integer>\n"
              << "TDEL <integer>\n"
              << "PRINT_BFS\n"
              << "PRINT_ZIGZAG\n"
              << "EXIT\n\n";

    while (std::cout << ">>> " && std::getline(std::cin, line))
    {
        if (line == "EXIT" || line == "exit")
            break;

        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command.empty())
            continue;

        else if (command == "TINSERT")
        {
            int value;
            ss >> value;

            if (isStreamFailed(ss))
                continue;

            myAVL.insert(value);
        }

        else if (command == "TDEL")
        {
            int value;
            ss >> value;

            if (isStreamFailed(ss))
                continue;

            myAVL.deleteVal(value);
        }

        else if (command == "TSEARCH")
        {
            int value;
            ss >> value;

            if (isStreamFailed(ss))
                continue;

            if (myAVL.find(value))
                std::cout << "Value '" << value << "' found.\n";
            else
                std::cout << "Value '" << value << "' not found.\n";
        }

        else if (command == "PRINT_BFS")
        {
            myAVL.BFSprint();
        }

        else if (command == "PRINT_ZIGZAG")
        {
            myAVL.zigZagPrint();
        }

        else
        {
            std::cout << "Error: Unknown command!\n";
        }
    }
    return 0;
}
