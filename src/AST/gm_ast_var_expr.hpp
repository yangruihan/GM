#pragma once

#include "../gm_common_header.h"
#include "gm_ast_tree.hpp"

#define VAR_TYPE_VALUE  0
#define VAR_TYPE_FUNC   1
#define VAR_TYPE_OTHER  2

namespace GM
{

    class GM_AST_VAR_EXPR : extends(GM_AST_TREE)
    {

    public:
        GM_AST_VAR_EXPR (std::string& token);
        ~GM_AST_VAR_EXPR () override;

    public:
        size_t get_need_child_count() const override;

        static bool check_token_valid(std::string& token);

        GM_Value* eval() override;

    protected:
        bool _check_childs_valid() const override;

        GM_Environment* before_set_environment(GM_Environment* env) override;

    protected:
        size_t m_var_type;

    };

}
