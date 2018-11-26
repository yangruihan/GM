#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{
    class GM_Environment;

    CREATE_NEW_ENV
    class GM_AST_LITERAL_EXPR : extends(GM_AST_TREE)
    {
    
    public:
        explicit GM_AST_LITERAL_EXPR (const std::string& token): GM_AST_TREE(token) {}
        ~GM_AST_LITERAL_EXPR () override = default;

    public:
        GM_AST_STR_FUNC(GM_AST_LITERAL_EXPR)

    protected:
        GM_Environment* before_set_environment(GM_Environment* env) override;

    };

}
