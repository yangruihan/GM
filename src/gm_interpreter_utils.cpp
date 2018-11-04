#include "gm_interpreter_utils.hpp"
#include "GM.h"

namespace GM
{
    
    GM_AST_TREE* GM_InterpreterUtils::check_token_is_operator(std::string& token)
    {
        if (GM_AST_ADD_OPERATOR_EXPR::check_token_valid(token))
        {
            return new GM_AST_ADD_OPERATOR_EXPR(token);
        }
        else if (GM_AST_SUB_OPERATOR_EXPR::check_token_valid(token))
        {
            return new GM_AST_SUB_OPERATOR_EXPR(token);
        }
        else if (GM_AST_MUL_OPERATOR_EXPR::check_token_valid(token))
        {
            return new GM_AST_MUL_OPERATOR_EXPR(token);
        }
        else if (GM_AST_DIV_OPERATOR_EXPR::check_token_valid(token))
        {
            return new GM_AST_DIV_OPERATOR_EXPR(token);
        }
        
        return nullptr;
    }
    
    GM_AST_TREE* GM_InterpreterUtils::check_token_is_number_literal(std::string& token)
    {
        auto token_size = token.size();
        
        if (GM_Utils::is_digit(token[0])
            || (token_size > 1 && (token[0] == '+' || token[0] == '-')))
        {
            bool is_float;
            if (GM_AST_NUMBER_LITERAL_EXPR::check_token_valid(token, is_float))
            {
                return new GM_AST_NUMBER_LITERAL_EXPR(token, is_float);
            }
        }
        
        return nullptr;
    }
    
    GM_AST_TREE *GM_InterpreterUtils::check_token_is_str_literal(std::string &token)
    {
        if (GM_AST_STR_LITERAL_EXPR::check_token_valid(token))
        {
            return new GM_AST_STR_LITERAL_EXPR(token);
        }
        
        return nullptr;
    }
    
    GM_AST_TREE *GM_InterpreterUtils::check_token_is_variable(std::string &token)
    {
        if (GM_AST_VAR_EXPR::check_token_valid(token))
        {
            return new GM_AST_VAR_EXPR(token);
        }

        return nullptr;
    }
    
}
