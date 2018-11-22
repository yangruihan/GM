#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_literal_expr.hpp"

namespace GM
{

    class GM_AST_NUMBER_LITERAL_EXPR : extends(GM_AST_LITERAL_EXPR)
    {
    
    protected:
        GM_AST_NUMBER_LITERAL_EXPR (const std::string& token, const bool& is_float);
        ~GM_AST_NUMBER_LITERAL_EXPR () override;

        friend class GM_MemoryManager;
        friend class GM_GarbageCollector;

    public:
        GM_AST_STR_FUNC(GM_AST_NUMBER_LITERAL_EXPR)

        size_t get_need_child_count() const override;

        static bool check_token_valid(const std::string& token, bool& is_float);

        GM_Value* eval() override;

        bool is_float() const { return m_is_float; }

    protected:
        bool _check_childs_valid() const override;

    protected:
        bool m_is_float;
    };

}
