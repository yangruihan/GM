#include "gm_custom_function.hpp"

#include "../../GM.h"
#include <sstream>
#include <stack>

namespace GM
{

    GM_CustomFuncValue::GM_CustomFuncValue(GM_Environment* env,
                                           const std::string& func_name,
                                           const size_t& param_count,
                                           const std::vector<std::string>* param_list,
                                           GM_AST_LIST_EXPR* func_body)
                                           : GM_Value(env),
                                             m_func_name(func_name),
                                             m_param_count(param_count),
                                             m_param_names(param_list),
                                             m_func_body(func_body)
    {
        // create a new environment
        auto new_env = new GM_Environment();
        new_env->set_parent(env);
        GM_Value::m_environment = new_env;

        // change env for func body
        func_body->set_environment(new_env);
        std::stack<GM_AST_TREE*> stack;
        for (size_t i = 0, count = func_body->get_child_count(); i < count; i++)
            stack.push(func_body->get_child(i));

        while (stack.size() > 0)
        {
            auto ast_tree = stack.top();
            stack.pop();
            ast_tree->set_environment(new_env);

            for (size_t i = 0, count = ast_tree->get_child_count(); i < count; i++)
                stack.push(ast_tree->get_child(i));
        }
    }

    GM_CustomFuncValue::~GM_CustomFuncValue()
    {
        delete m_param_names;
        delete m_func_body;
    }
    
    void GM_CustomFuncValue::_init_functions() {}

    std::string GM_CustomFuncValue::str() const
    {
        std::ostringstream stream;
        stream << "[" << m_func_name << " (";

        for (size_t i = 0, count = m_param_names->size() - 1; i < count; i++)
            stream << (*m_param_names)[i] << ", ";
        stream << (*m_param_names)[m_param_names->size() - 1] << ")]";

        return stream.str();
    }

    bool GM_CustomFuncValue::check_func_name_valid(const std::string &func_name)
    {
        if (GM_Utils::is_digit(func_name[0]))
            return false;

        return true;
    }

    GM_Value* GM_CustomFuncValue::eval()
    {
        auto ret = m_func_body->eval();
        auto list_value = dynamic_cast<GM_ListValue*>(ret);
        if (list_value == nullptr)
            return ret;

        return (*list_value)[list_value->get_item_count() - 1];
    }

}
