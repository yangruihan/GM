#pragma once

#include "../Core/gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{

    class GM_AST_BINARY_EXPR : extends(GM_AST_TREE)
    {

    public:
        GM_AST_BINARY_EXPR (const std::string& token): GM_AST_TREE(token) {}
        ~GM_AST_BINARY_EXPR () override {};

    public:
        GM_AST_STR_FUNC(GM_AST_BINARY_EXPR)

    };

}
