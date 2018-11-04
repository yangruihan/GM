#pragma once

#include "../gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{

    class GM_AST_BINARY_EXPR : extends(GM_AST_TREE)
    {
    public:
        GM_AST_BINARY_EXPR (std::string& token): GM_AST_TREE(token) {}
        ~GM_AST_BINARY_EXPR () override {};
    };

}
