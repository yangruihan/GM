#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_tree.hpp"

#define VAR_TYPE_VALUE      0
#define VAR_TYPE_FUNC       1
#define VAR_TYPE_OTHER      2
#define VAR_TYPE_VAR_NAME   3

namespace GM
{
    class GM_VarNameValue;

    class GM_AST_VAR_EXPR : extends(GM_AST_TREE)
    {

    public:
        GM_AST_VAR_EXPR (const std::string& token);
        ~GM_AST_VAR_EXPR () override;

    public:
        GM_AST_STR_FUNC(GM_AST_VAR_EXPR)

        static GM_VarNameValue* convert_var_name_value(GM_AST_TREE* tree);

        size_t get_need_child_count() const override;

        static bool check_token_valid(const std::string& token);

        GM_Value* eval() override;

        GM_VarNameValue* get_var_name_value() const;

        GM_Value* get_value() const;

    protected:
        bool _check_childs_valid() const override;

        GM_Environment* before_set_environment(GM_Environment* env) override;

    };

}
