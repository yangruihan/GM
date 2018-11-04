#include "gm_ast_var_expr.hpp"
#include "../GM.h"

#include <vector>

namespace GM
{
    GM_AST_VAR_EXPR::GM_AST_VAR_EXPR(std::string& token)
                                    : GM_AST_TREE(token)
    {}

    GM_AST_VAR_EXPR::~GM_AST_VAR_EXPR()
    {}

    size_t GM_AST_VAR_EXPR::get_need_child_count() const
    {
        if (m_var_type == VAR_TYPE_VALUE)
        {
            return 0;
        }
        else if (m_var_type == VAR_TYPE_FUNC)
        {
            auto object = m_environment->get_var(m_token);
            auto func = dynamic_cast<GM_Function*>(object);
            return func->get_param_count();
        }
        else
        {
            return 0;
        }
    }

    bool GM_AST_VAR_EXPR::check_token_valid(std::string &token)
    {
        if (GM_Utils::is_digit(token[0]))
            return false;

        for (size_t i = 1; i < token.size(); i++)
        {
            if (!GM_Utils::is_alpha(token[i]) && token[i] != '_')
                return false;
        }

        return true;
    }

    GM_Value *GM_AST_VAR_EXPR::eval()
    {
        auto object = m_environment->get_var(m_token);
        if (object == nullptr)
            return nullptr;

        if (m_var_type == VAR_TYPE_VALUE)
        {
            return (dynamic_cast<GM_Value*>(object));
        }
        else if (m_var_type == VAR_TYPE_FUNC)
        {
            auto func = dynamic_cast<GM_Function*>(object);
            auto list_param = new std::vector<GM_Value*>();
            for (size_t i = 0, count = get_child_count(); i < count; i++)
            {
                list_param->push_back(get_child(i)->eval());
            }
            auto parameter = new GM_Parameter(list_param, nullptr);
            return func->eval(parameter);
        }
        else
        {
            return nullptr;
        }
    }

    bool GM_AST_VAR_EXPR::_check_childs_valid() const
    {
        return true;
    }
    
    GM_Environment *GM_AST_VAR_EXPR::on_set_environment(GM_Environment *env)
    {
        auto object = m_environment->get_var(m_token);
        if (object == nullptr)
        {
            PRINT_ERROR_F("UndefinedError: cannot find symbol '%s'", m_token.c_str());
            return env;
        }

        if (GM_Utils::is_instance_of<GM_Object, GM_Value>(object))
        {
            m_var_type = VAR_TYPE_VALUE;
        }
        else if (GM_Utils::is_instance_of<GM_Object, GM_Function>(object))
        {
            m_var_type = VAR_TYPE_FUNC;
        }
        else
        {
            m_var_type = VAR_TYPE_OTHER;
        }

        return env;
    }

}
