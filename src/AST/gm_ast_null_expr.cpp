#include "gm_ast_null_expr.hpp"

#include "GM.h"

namespace GM
{

    GM_AST_NULL_EXPR::GM_AST_NULL_EXPR(const std::string& token): GM_AST_TREE(token)
    {}

    GM_AST_NULL_EXPR::~GM_AST_NULL_EXPR() = default;

    bool GM_AST_NULL_EXPR::_check_childs_valid() const
    {
        return true;
    }

    GM_Value *GM_AST_NULL_EXPR::eval()
    {
        return GM_Value::null_value();
    }

    size_t GM_AST_NULL_EXPR::get_need_child_count() const
    {
        return 0;
    }

}
