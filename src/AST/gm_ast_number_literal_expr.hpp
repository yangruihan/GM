#pragma once

#include "../GM.h"
#include "gm_ast_literal_expr.hpp"

namespace GM
{

    class GM_AST_NUMBER_LITERAL_EXPR : extends(GM_AST_LITERAL_EXPR)
    {
    
    public:
        GM_AST_NUMBER_LITERAL_EXPR (std::string& token, const bool& is_float);
        ~GM_AST_NUMBER_LITERAL_EXPR () override;

    public:
        size_t get_need_child_count() const override;

        static bool check_token_valid(std::string& token, bool& is_float);

        GM_Value* eval() override;

    protected:
        bool _check_childs_valid() const override;

    protected:
        bool m_is_float;
    };

}