#include "gm_ast_math_operator_expr.hpp"
#include "../Type/gm_list_value.hpp"
#include "../Type/gm_function.hpp"

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
            auto func = left_value->get_func(FUNC_ADD_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_ADD_OP_KEY);
                return nullptr;
            }
            
            auto parameters = new GM_ListValue();
            parameters->add_item(left_value)->add_item(right_value);
            
            return func->eval(parameters);
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
            auto func = left_value->get_func(FUNC_SUB_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameters = new GM_ListValue();
            parameters->add_item(left_value)->add_item(right_value);
            
            return func->eval(parameters);
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
            auto func = left_value->get_func(FUNC_MUL_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_MUL_OP_KEY);
                return nullptr;
            }
            
            auto parameters = new GM_ListValue();
            parameters->add_item(left_value)->add_item(right_value);
            
            return func->eval(parameters);
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
            auto func = left_value->get_func(FUNC_DIV_OP_KEY);
            if (func == nullptr)
            {
                PRINT_ERROR_F("FunctionError: %s not found", FUNC_DIV_OP_KEY);
                return nullptr;
            }
            
            auto parameters = new GM_ListValue();
            parameters->add_item(left_value)->add_item(right_value);
            
            return func->eval(parameters);
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