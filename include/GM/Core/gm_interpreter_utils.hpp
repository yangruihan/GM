#pragma once

#include "gm_common_header.h"

namespace GM
{
    class GM_AST_TREE;
    
    class GM_InterpreterUtils : extends(GM_Object)
    {
        
    public:
        static GM_AST_TREE* check_token_is_operator(const std::string& token);
        
        static GM_AST_TREE* check_token_is_number_literal(const std::string& token);
        
        static GM_AST_TREE* check_token_is_str_literal(const std::string& token);

        static GM_AST_TREE* check_token_is_variable(const std::string& token);

        static GM_AST_TREE* check_token_is_list(const std::string& token);

        static GM_AST_TREE* check_token_is_dict(const std::string& token);
        
    };
    
}
