#pragma once

#include "gm_ast_tree.hpp"
#include "../gm_common_header.h"

namespace GM
{

    class GM_AST_NULL_EXPR : extends(GM_AST_TREE)
    {
    public:
        GM_AST_NULL_EXPR (const std::string& token);
        ~GM_AST_NULL_EXPR () override;

    public:
        size_t get_need_child_count() const override;

        GM_Value* eval() override;

    protected:

        bool _check_childs_valid() const override;
    };

}
