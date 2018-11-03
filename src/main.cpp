#include <stdio.h>
#include <iostream>
#include <string>

#include "GM.h"
#include "gm_interpreter.hpp"
#include "AST/gm_ast_tree.hpp"

using namespace GM;

#ifdef DEBUG

void print_ast(GM_AST_TREE* node, int indent)
{
    if (node == nullptr)
    {
        DEBUG_ERROR("node is nullptr");
        return;
    }

    std::cout << std::endl;

    for (size_t i = 0; i < indent; i++)
    {
        std::cout << "\t";
    }

    printf("(Token: %s, child count: %d)", 
                        node->get_token().c_str(),
                        node->get_child_count());

    for (size_t i = 0; i < node->get_child_count(); i++)
    {
        print_ast(node->get_child(i), indent + 1);
    }
}

#endif // DEBUG


int main()
{
    DEBUG_LOG_F("----- GM Interpreter [Version %d.%d.%d]-----", 0, 0, 1);

    GM_Interpreter* interpreter = new GM_Interpreter();

    std::string command;
    int ret = 0;
    while (true)
    {
        std::cout << "> ";

        std::getline(std::cin, command);
        DEBUG_LOG_F("-- Input: %s", command.c_str());
        
        ret = interpreter->parse(command);

        if (ret == 0)
        {
            DEBUG_LOG_F("Create AST success");
            DEBUG_LOG_F("--- Show AST structure ---");
            auto root = interpreter->get_ast_root();
                        
            #ifdef DEBUG
            
            print_ast(root, 0);
            std::cout << std::endl;
    
            #endif // DEBUG

            auto result = interpreter->eval();
            if (result != nullptr)
            {
                PRINT_LOG_F("Result: %s", result->str().c_str());
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}