#pragma once

#include "gm_common_header.h"

namespace GM
{
    class GM_AST_TREE;
    
    class GM_InterpreterUtils : extends(GM_Object)
    {
        
    public:
        static GM_AST_TREE* check_token_is_operator(std::string& token);
        
        static GM_AST_TREE* check_token_is_number_literal(std::string& token);
        
        static GM_AST_TREE* check_token_is_str_literal(std::string& token);

        static GM_AST_TREE* check_token_is_variable(std::string& token);
        
    };
    
}
