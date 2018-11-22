#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_literal_expr.hpp"

namespace GM
{
    class GM_AST_STR_LITERAL_EXPR : extends(GM_AST_LITERAL_EXPR)
    {
        
    public:
        GM_AST_STR_LITERAL_EXPR (const std::string& token);
        ~GM_AST_STR_LITERAL_EXPR () override;
        
    public:
        GM_AST_STR_FUNC(GM_AST_STR_LITERAL_EXPR)

        size_t get_need_child_count() const override;
        
        static bool check_token_valid(const std::string& token);
        
        GM_Value* eval() override;
        
    protected:
        bool _check_childs_valid() const override;

    };

}
