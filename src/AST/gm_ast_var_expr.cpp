#include "gm_ast_var_expr.hpp"
#include "GM.h"

#include <vector>

namespace GM
{
    GM_AST_VAR_EXPR::GM_AST_VAR_EXPR(const std::string& token)
                                    : GM_AST_TREE(token)
    {}

    GM_AST_VAR_EXPR::~GM_AST_VAR_EXPR() = default;

    size_t GM_AST_VAR_EXPR::get_need_child_count() const
    {
        return GM_AST_VARIADIC_PARAMS_FLAG;
    }

    bool GM_AST_VAR_EXPR::check_token_valid(const std::string &token)
    {
        return !GM_Utils::is_digit(token[0]);
    }

    GM_Value* GM_AST_VAR_EXPR::eval()
    {
        auto object = m_environment->get_var(m_token);
        if (object == nullptr)
            return GM_Value::var_name_value(get_environment(), m_token);

        auto func = dynamic_cast<GM_Function*>(object);
        if (func != nullptr)
        {
            auto count = get_child_count();

            if (count == 0 && func->get_param_count() > 0)
            {
                GM_Value::var_name_value(get_environment(), m_token);
            }
            else
            {
                auto list_param = new std::vector<GM_Object*>(count);
                for (size_t i = 0; i < count; i++)
                {
                    (*list_param)[i] = (get_child(i));
                }
                auto parameter = new GM_Parameter(get_environment(),
                                                  list_param, nullptr);
                return func->eval(parameter);
            }
        }

        auto cust_func = dynamic_cast<GM_CustomFuncValue*>(object);
        if (cust_func != nullptr)
        {
            if (get_child_count() == 0)
            {
                return cust_func;
            }
            else
            {
                auto env = GM_Environment::create(cust_func->get_environment());

                // prepare parameters
                for (size_t i = 0, count = cust_func->get_param_count(); i < count; i++)
                {
                    const auto value = get_child(i)->eval();
                    env->set_var(cust_func->get_param_name(i), value);
                }

                GM_Utils::set_env_for_childs(cust_func->get_func_body(), env);
                const auto ret = cust_func->eval();
                GM_Utils::set_env_for_childs(cust_func->get_func_body(),
                                             cust_func->get_environment());

//                GM_GC::free(env);

                return ret;
            }
        }

        const auto value = GM_Value::convert_to_value(object);
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

    GM_Value* GM_AST_VAR_EXPR::get_value() const
    {
        return m_environment->get_var(m_token);
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
