#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{

    class GM_AST_DICT_EXPR : extends(GM_AST_TREE)
    {

    public:
        GM_AST_DICT_EXPR (const std::string& token);
        ~GM_AST_DICT_EXPR () override;

    public:
        GM_AST_STR_FUNC(GM_AST_DICT_EXPR)

        size_t get_need_child_count() const override;

        static bool check_token_valid(const std::string& token);

        GM_Value* eval() override;

    protected:
        GM_Environment* before_set_environment(GM_Environment* env) override;

        bool _check_childs_valid() const override;
        
    };
    
}
