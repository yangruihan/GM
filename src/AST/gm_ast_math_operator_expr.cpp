#include "gm_ast_math_operator_expr.hpp"
#include "GM.h"

namespace GM
{

    GM_Value* GM_AST_ADD_OPERATOR_EXPR::eval()
    {
        if (!_check_childs_valid())
        {
            return nullptr;
        }

        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            auto func = left_value->get_cur_env_func(FUNC_ADD_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_ADD_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            const auto ret = func->eval(parameter);
            GM_GC::free(parameter);
            return ret;
        }

        return nullptr;
    }

    bool GM_AST_ADD_OPERATOR_EXPR::_check_childs_valid() const
    {
        if (m_childs == nullptr)
            return false;

        if (get_child_count() != 2)
            return false;

        if (get_child(0) == nullptr || get_child(1) == nullptr)
            return false;

        return true;
    }

    GM_Value* GM_AST_SUB_OPERATOR_EXPR::eval()
    {
        if (!_check_childs_valid())
        {
            return nullptr;
        }

        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            auto func = left_value->get_cur_env_func(FUNC_SUB_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            const auto ret = func->eval(parameter);
            GM_GC::free(parameter);
            return ret;
        }

        return nullptr;
    }

    bool GM_AST_SUB_OPERATOR_EXPR::_check_childs_valid() const
    {
        if (m_childs == nullptr)
            return false;

        if (get_child_count() != 2)
            return false;

        if (get_child(0) == nullptr || get_child(1) == nullptr)
            return false;

        return true;
    }

    GM_Value* GM_AST_MUL_OPERATOR_EXPR::eval()
    {
        if (!_check_childs_valid())
        {
            return nullptr;
        }

        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            auto func = left_value->get_cur_env_func(FUNC_MUL_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_MUL_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            const auto ret = func->eval(parameter);
            GM_GC::free(parameter);
            return ret;
        }

        return nullptr;
    }

    bool GM_AST_MUL_OPERATOR_EXPR::_check_childs_valid() const
    {
        if (m_childs == nullptr)
            return false;

        if (get_child_count() != 2)
            return false;

        if (get_child(0) == nullptr || get_child(1) == nullptr)
            return false;

        return true;
    }

    GM_Value* GM_AST_DIV_OPERATOR_EXPR::eval()
    {
        if (!_check_childs_valid())
        {
            return nullptr;
        }

        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            auto func = left_value->get_cur_env_func(FUNC_DIV_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_DIV_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            const auto ret = func->eval(parameter);
            GM_GC::free(parameter);
            return ret;
        }

        return nullptr;
    }

    bool GM_AST_DIV_OPERATOR_EXPR::_check_childs_valid() const
    {
        if (m_childs == nullptr)
            return false;

        if (get_child_count() != 2)
            return false;

        if (get_child(0) == nullptr || get_child(1) == nullptr)
            return false;

        return true;
    }

}
