#include "gm_ast_number_literal_expr.hpp"
#include "../Common/gm_utils.hpp"
#include "../Type/gm_types_header.h"

namespace GM
{

    GM_AST_NUMBER_LITERAL_EXPR::GM_AST_NUMBER_LITERAL_EXPR(std::string& token,
                                                           const bool& is_float)
                                                           : GM_AST_LITERAL_EXPR(token),
                                                             m_is_float(is_float)
    {}

    GM_AST_NUMBER_LITERAL_EXPR::~GM_AST_NUMBER_LITERAL_EXPR() {}

    size_t GM_AST_NUMBER_LITERAL_EXPR::get_need_child_count() const 
    {
        return 0;
    }

    bool GM_AST_NUMBER_LITERAL_EXPR::check_token_valid(std::string& token, bool& is_float)
    {
        auto token_len = token.size();
        auto start_pos = token[0] == '+' || token[0] == '-' ? 1 : 0;
        is_float = false;

        for(size_t i = start_pos; i < token_len; i++)
        {
            if (token[i] == '.')
            {
                if (is_float == false)
                    is_float = true;
                else
                    return false;
            }
            else if (!GM_Utils::is_digit(token[i]))
            {
                return false;
            }
        }

        return true;
    }

    GM_Value* GM_AST_NUMBER_LITERAL_EXPR::eval()
    {
        if (m_is_float)
            return new GM_FloatValue(m_token);
        else
            return new GM_IntValue(m_token);
    }

    bool GM_AST_NUMBER_LITERAL_EXPR::_check_childs_valid() const
    {
        return true;
    }

} // namespace GM
