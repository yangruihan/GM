#include "gm_utils.hpp"

#include <stack>
#include <sstream>
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

    std::string GM_Utils::vector_str(const std::vector<GM_Object*>* vector)
    {
        if (vector == nullptr)
            return "[vector is nullptr]";

        std::ostringstream stream;
        stream << "[";
        auto count = vector->size() - 1;
        for (size_t i = 0; i < count; i++)
        {
            stream << (*vector)[i]->str() << ", ";
        }
        stream << (*vector)[count]->str() << "]";
        return stream.str();
    }

    std::string GM_Utils::dict_str(const std::map<std::string, GM_Object *> *dict)
    {
        if (dict == nullptr)
            return "{dict is nullptr}";

        std::ostringstream stream;
        stream << "{";
        for (auto it = dict->begin(); it != dict->end(); it++)
        {
            stream << '\"' << it->first << '\"' << ": " << it->second << std::endl;
        }
        stream << "}";
        return stream.str();
    }

}
