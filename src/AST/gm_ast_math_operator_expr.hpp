#pragma once

#include "../GM.h"
#include "gm_ast_binary_expr.hpp"

namespace GM
{

    class GM_AST_PLUS_OPERATOR_EXPR : extends(GM_AST_BINARY_EXPR)
    {

    public:
        GM_AST_PLUS_OPERATOR_EXPR () {}
        ~GM_AST_PLUS_OPERATOR_EXPR () override {}

    public:
        size_t get_need_child_count() const override { return 2; };
    };

}
