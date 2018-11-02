#include <iostream>
#include <string>

#include "GM.h"
#include "gm_interpreter.hpp"

using namespace GM;

int main()
{
    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);

    GM_Interpreter* interpreter = new GM_Interpreter();

    std::string* command = new std::string();
    int ret = 0;
    while (true)
    {
        std::getline(std::cin, *command);
        DEBUG_LOG_F("-- Input: %s", command->c_str());
        
        ret = interpreter->parse(command);

        if (ret != 0)
            break;
    }

    return 0;
}