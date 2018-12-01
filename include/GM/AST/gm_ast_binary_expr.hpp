#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{
    
    KEEP_ENV
    class GM_AST_BINARY_EXPR : extends(GM_AST_TREE)
    {

    public:
        explicit GM_AST_BINARY_EXPR (const std::string& token)
            : GM_AST_TREE(token, 2) {}
        ~GM_AST_BINARY_EXPR () override = default;

    public:
        GM_AST_STR_FUNC(GM_AST_BINARY_EXPR)

    };

}
