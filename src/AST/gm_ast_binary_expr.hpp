#pragma once

#include "../GM.h"
#include "gm_ast_tree.hpp"

namespace GM
{

    class GM_AST_BINARY_EXPR : extends(GM_AST_TREE)
    {
    public:
        GM_AST_BINARY_EXPR () {}
        ~GM_AST_BINARY_EXPR () override = 0;
    };

}