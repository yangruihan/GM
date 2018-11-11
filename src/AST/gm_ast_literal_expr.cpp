#include "gm_ast_literal_expr.hpp"

#include "GM.h"

namespace GM
{

    GM_Environment* GM_AST_LITERAL_EXPR::before_set_environment(GM_Environment* env)
    {
        return GM_Environment::create(env);
    }

}
