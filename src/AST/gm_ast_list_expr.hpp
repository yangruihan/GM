#pragma once

#include "../gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{

    class GM_AST_LIST_EXPR : extends(GM_AST_TREE)
    {

    public:
        GM_AST_LIST_EXPR (const std::string& token);
        ~GM_AST_LIST_EXPR () override;

    public:
        size_t get_need_child_count() const override;

        static bool check_token_valid(const std::string& token);

        GM_Value* eval() override;

    protected:
        bool _check_childs_valid() const override;

    };

}
