#include <cstdio>
#include <iostream>
#include <string>

#include "GM.h"

using namespace GM;

void repl(GM_Interpreter* interpreter)
{
    interpreter->repl();
}

void parse_files(const int argc, char* argv[], GM_Interpreter* interpreter)
{
    for (auto i = 1; i < argc; i++)
    {
        const std::string file_path = argv[i];
        interpreter->parse_file(file_path);
    }
}

int main(const int argc, char* argv[])
{
    DEBUG_LOG("\n\n\n");

    DEBUG_LOG("- GM parameters ---");

#ifdef DEBUG
    for (auto i = 0; i < argc; i++)
    {
        DEBUG_LOG_F("- %d: %s", i, argv[i]);
    }
#endif

    DEBUG_LOG("-------------------");

    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);

    // ----- init part -----
    GM_GC::init();
    GM_Interpreter::init();

    const auto interpreter = GM_Interpreter::instance();

    if (argc == 1)
        repl(interpreter);
    else
        parse_files(argc, argv, interpreter);

    GM_Interpreter::destory();
    
    GM_GC::gc();
#ifdef DEBUG
    GM_GC::dump(std::cout, GM::on_dump_obj_handler);
#endif
    GM_GC::destroy();

#ifdef _WINDOWS
    int pause;
    std::cin >> pause;
#endif

    return 0;
}
