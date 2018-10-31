#include <iostream>

#include "gm_interpreter.h"

#define MAX_COMMAND_CHAR 256

using namespace GM;

int main()
{
    std::cout << "----- GM Interpreter -----" << std::endl;

    GM_Interpreter* interpreter = new GM_Interpreter();

    char* command = new char[MAX_COMMAND_CHAR];
    int ret = 0;
    while (true)
    {
        std::cin.getline(command, MAX_COMMAND_CHAR);
        ret = interpreter->parse(command);

        if (ret != 0)
            break;
    }

    return 0;
}