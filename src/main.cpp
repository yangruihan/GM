#include <stdio.h>
#include <iostream>
#include <string>

#include "GM.h"

using namespace GM;

void repl(GM_Interpreter* interpreter)
{
    interpreter->set_parse_mode(GM_INTERPRETER_REPL_MODE);

    std::string command;
    bool running_flag = true;
    while (running_flag)
    {
        std::cout << "> ";
        std::getline(std::cin, command);

        DEBUG_LOG_F("-- Input: %s", command.c_str());

        interpreter->parse_and_eval(command);

        running_flag = interpreter->get_running_flag();
    }
}

void parse_files(int argc, char* argv[], GM_Interpreter* interpreter)
{
    interpreter->set_parse_mode(GM_INTERPRETER_FILE_MODE);

    std::string file_name;
    std::string file_content;
    for (size_t i = 0; i < argc; i++)
    {
        file_name = argv[i];
        if (GM_Utils::str_ends_with(file_name, GM_SOURCE_FILE_SUFFIX))
        {
            if (GM_Utils::read_file(file_name.c_str(), file_content))
            {
                DEBUG_LOG_F("File content: %s", file_content.c_str());

                interpreter->parse_and_eval(file_content);
            }
            else
            {
                PRINT_ERROR_F("IOError: file(%s) read failed", file_name.c_str());
            }
        }
    }
}

int main(int argc, char* argv[])
{
    DEBUG_LOG("\n\n\n");

    DEBUG_LOG("- GM parameters ---");

#ifdef DEBUG
    for (size_t i = 0; i < argc; i++)
    {
        DEBUG_LOG_F("- %zu: %s", i, argv[i]);
    }
#endif

    DEBUG_LOG("-------------------");

    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);

    GM_Interpreter* interpreter = GM_Interpreter::instance();

    if (argc == 1)
        repl(interpreter);
    else
        parse_files(argc, argv, interpreter);

    GM_Interpreter::destory();

    return 0;
}
