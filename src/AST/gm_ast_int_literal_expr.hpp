#pragma once

#include "../GM.h"
#include "gm_ast_literal_expr.hpp"

namespace GM
{

    class GM_AST_INT_LITERAL_EXPR : extends(GM_AST_LITERAL_EXPR)
    {
    
    public:
        GM_AST_INT_LITERAL_EXPR (std::string& token);
        ~GM_AST_INT_LITERAL_EXPR () override;

    public:
        size_t get_need_child_count() const override;

        static bool check_token_valid(std::string& token);
    };

}