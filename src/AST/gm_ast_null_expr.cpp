#include "gm_ast_null_expr.hpp"

#include "GM.h"

namespace GM
{

    GM_AST_NULL_EXPR::GM_AST_NULL_EXPR(const std::string& token)
        : GM_AST_TREE(token, 0)
    {}

    GM_Value *GM_AST_NULL_EXPR::eval()
    {
        return GM_Value::null_value();
    }

}
