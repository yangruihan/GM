#include "gm_ast_str_literal_expr.hpp"
#include "../GM.h"

namespace GM
{
    

    GM_AST_STR_LITERAL_EXPR::GM_AST_STR_LITERAL_EXPR (std::string& token)
                                                : GM_AST_LITERAL_EXPR(token)
    {
    }
    
    GM_AST_STR_LITERAL_EXPR::~GM_AST_STR_LITERAL_EXPR () {}
    

    size_t GM_AST_STR_LITERAL_EXPR::get_need_child_count() const
    {
        return 0;
    }
    
    bool GM_AST_STR_LITERAL_EXPR::check_token_valid(std::string& token)
    {
        auto token_len = token.size();
        if (token_len < 2)
            return false;
        
        if (token[0] != '"' || token[token_len - 1] != '"')
            return false;
        
        return true;
    }
    
    GM_Value* GM_AST_STR_LITERAL_EXPR::eval()
    {
        if (_check_childs_valid())
            return new GM_StrValue(m_token.substr(1, m_token.size() - 2));
        
        return nullptr;
    }
    

    bool GM_AST_STR_LITERAL_EXPR::_check_childs_valid() const
    {
        return true;
    }
    
}
