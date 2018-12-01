#include "gm_ast_bool_literal_expr.hpp"
#include "GM.h"

namespace GM
{

    GM_AST_BOOL_LITERAL_EXPR::GM_AST_BOOL_LITERAL_EXPR(const std::string& token, const bool& value)
        : GM_AST_LITERAL_EXPR(token), m_value(value)
    {}

    GM_Value* GM_AST_BOOL_LITERAL_EXPR::eval()
    {
        return GM_Value::bool_value(get_environment(), m_value);
    }

}