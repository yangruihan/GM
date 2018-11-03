#include "gm_ast_int_literal_expr.hpp"
#include "../Common/gm_utils.hpp"
#include "../Type/gm_int_value.hpp"

namespace GM
{

    GM_AST_INT_LITERAL_EXPR::GM_AST_INT_LITERAL_EXPR(std::string& token): GM_AST_LITERAL_EXPR(token)
    {}

    GM_AST_INT_LITERAL_EXPR::~GM_AST_INT_LITERAL_EXPR() {}

    size_t GM_AST_INT_LITERAL_EXPR::get_need_child_count() const 
    {
        return 0;
    }

    bool GM_AST_INT_LITERAL_EXPR::check_token_valid(std::string& token)
    {
        auto token_len = token.size();
        auto start_pos = token[0] == '+' || token[0] == '-' ? 1 : 0;
        
        for(size_t i = start_pos; i < token_len; i++)
        {
            if (!GM_Utils::is_digit(token[i]))
                return false;
        }

        return true;
    }

    GM_Value* GM_AST_INT_LITERAL_EXPR::eval()
    {
        return new GM_IntValue(m_token);
    }

    bool GM_AST_INT_LITERAL_EXPR::_check_childs_valid() const
    {
        return true;
    }

} // namespace GM
