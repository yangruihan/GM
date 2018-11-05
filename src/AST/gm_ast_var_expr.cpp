#include "gm_ast_var_expr.hpp"
#include "../GM.h"

#include <vector>

namespace GM
{
    GM_AST_VAR_EXPR::GM_AST_VAR_EXPR(const std::string& token)
                                    : GM_AST_TREE(token)
    {}

    GM_AST_VAR_EXPR::~GM_AST_VAR_EXPR()
    {}

    size_t GM_AST_VAR_EXPR::get_need_child_count() const
    {
        auto object = m_environment->get_current_env_var(m_token);
        if (object == nullptr)
            return 0;

        if (GM_Utils::is_instance_of<GM_Object, GM_Function>(object))
        {
            auto func = dynamic_cast<GM_Function*>(object);
            return func->get_param_count();
        }
        else if (GM_Utils::is_instance_of<GM_Object, GM_CustomFuncValue>(object))
        {
            auto func = dynamic_cast<GM_CustomFuncValue*>(object);
            return func->get_param_count();
        }
        else if (GM_Utils::is_instance_of<GM_Object, GM_Value>(object))
        {
            return 0;
        }

        return 0;
    }

    bool GM_AST_VAR_EXPR::check_token_valid(const std::string &token)
    {
        if (GM_Utils::is_digit(token[0]))
            return false;

        return true;
    }

    GM_Value* GM_AST_VAR_EXPR::eval()
    {
        auto object = m_environment->get_var(m_token);
        if (object == nullptr)
            return GM_Value::var_name_value(get_environment(), m_token);

        auto func = dynamic_cast<GM_Function*>(object);
        if (func != nullptr)
        {
            auto list_param = new std::vector<GM_Object*>();
            for (size_t i = 0, count = get_child_count(); i < count; i++)
            {
                list_param->push_back(get_child(i));
            }
            auto parameter = new GM_Parameter(get_environment(),
                                              list_param, nullptr);
            return func->eval(parameter);
        }

        auto cust_func = dynamic_cast<GM_CustomFuncValue*>(object);
        if (cust_func != nullptr)
        {
            auto env = cust_func->get_environment();

            // prepare parameters
            for (size_t i = 0, count = cust_func->get_param_count(); i < count; i++)
            {
                auto value = get_child(i)->eval();
                env->set_var(cust_func->get_param_name(i), value);
            }

            return cust_func->eval();
        }

        auto value = GM_Value::convert_to_value(object);
        if (value != nullptr)
            return value;

        return nullptr;
    }

    GM_VarNameValue* GM_AST_VAR_EXPR::convert_var_name_value(GM_AST_TREE* tree)
    {
        auto var_expr = dynamic_cast<GM_AST_VAR_EXPR*>(tree);
        if (var_expr == nullptr)
            return nullptr;

        return var_expr->get_var_name_value();
    }

    GM_VarNameValue* GM_AST_VAR_EXPR::get_var_name_value() const
    {
        return GM_Value::var_name_value(m_environment, m_token);
    }

    bool GM_AST_VAR_EXPR::_check_childs_valid() const
    {
        return true;
    }
    
    GM_Environment *GM_AST_VAR_EXPR::before_set_environment(GM_Environment *env)
    {
        return env;
    }

}
