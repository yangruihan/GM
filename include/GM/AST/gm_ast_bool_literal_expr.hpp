#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_literal_expr.hpp"

namespace GM
{

    CREATE_NEW_ENV
    class GM_AST_BOOL_LITERAL_EXPR : extends(GM_AST_LITERAL_EXPR)
    {

    public:
        explicit GM_AST_BOOL_LITERAL_EXPR(const std::string& token,
                                          const bool& value);
        ~GM_AST_BOOL_LITERAL_EXPR() override = default;

    public:
        GM_AST_STR_FUNC(GM_AST_BOOL_LITERAL_EXPR)

        size_t get_need_child_count() const override 
        { return 0; }

        GM_Value* eval() override;

    protected:
        bool m_value;

    };

}