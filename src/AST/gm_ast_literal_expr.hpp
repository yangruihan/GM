#pragma once

#include "../gm_common_header.h"
#include "gm_ast_tree.hpp"

namespace GM
{
    class GM_Environment;

    class GM_AST_LITERAL_EXPR : extends(GM_AST_TREE)
    {
    public:
        GM_AST_LITERAL_EXPR (const std::string& token): GM_AST_TREE(token) {}
        ~GM_AST_LITERAL_EXPR () override {};

    protected:
        GM_Environment* before_set_environment(GM_Environment* env) override;

    };

}
