#include "gm_utils.hpp"

#include <stack>
#include "../GM.h"

namespace GM
{

    GM_Environment* GM_Utils::set_env_for_childs(GM_AST_TREE* tree, GM_Environment* parent)
    {
        // create a new environment
        auto new_env = new GM_Environment();
        new_env->set_parent(parent);

        // change env for func body
        tree->set_environment(new_env);
        std::stack<GM_AST_TREE*> stack;
        for (size_t i = 0, count = tree->get_child_count(); i < count; i++)
            stack.push(tree->get_child(i));

        while (stack.size() > 0)
        {
            auto ast_tree = stack.top();
            stack.pop();
            ast_tree->set_environment(new_env);

            for (size_t i = 0, count = ast_tree->get_child_count(); i < count; i++)
                stack.push(ast_tree->get_child(i));
        }

        return new_env;
    }

}
