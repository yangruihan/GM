#include <stdio.h>
#include <iostream>
#include <string>

#include "GM.h"

using namespace GM;

void repl(GM_Interpreter* interpreter)
{
    interpreter->repl();
}

void parse_files(int argc, char* argv[], GM_Interpreter* interpreter)
{
    std::string file_path;
    for (size_t i = 0; i < argc; i++)
    {
        file_path = argv[i];
        interpreter->parse_file(file_path);
    }
}

int main(int argc, char* argv[])
{
    DEBUG_LOG("\n\n\n");

    DEBUG_LOG("- GM parameters ---");

#ifdef DEBUG
    for (auto i = 0; i < argc; i++)
    {
        DEBUG_LOG_F("- %zu: %s", i, argv[i]);
    }
#endif

    DEBUG_LOG("-------------------");

    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);
    
    GM_GC::init();
    GM_Interpreter::init();
    
    const auto interpreter = GM_Interpreter::instance();

    if (argc == 1)
        repl(interpreter);
    else
        parse_files(argc, argv, interpreter);

    GM_Interpreter::destory();
    
    GM_GC::gc();
    GM_GC::dump(std::cout);
    GM_GC::destroy();

    int pause;
    std::cin >> pause;

    return 0;
}
