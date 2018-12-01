#pragma once

#include "gm_ast_tree.hpp"
#include "../Core/gm_common_header.h"

namespace GM
{
    KEEP_ENV
    class GM_AST_NULL_EXPR : extends(GM_AST_TREE)
    {
    public:
        explicit GM_AST_NULL_EXPR (const std::string& token);
        ~GM_AST_NULL_EXPR () override = default;

    public:
        GM_AST_STR_FUNC(GM_AST_NULL_EXPR)

        size_t get_need_child_count() const override { return 0; }

        GM_Value* eval() override;

    };

}
