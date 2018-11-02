#include <iostream>

#include "GM.h"
#include "gm_interpreter.hpp"

#define MAX_COMMAND_CHAR 256

using namespace GM;

int main()
{
    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);

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