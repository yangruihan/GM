#include "gm_ast_math_operator_expr.hpp"
#include "GM.h"

namespace GM
{

    GM_Value* GM_AST_ADD_OPERATOR_EXPR::eval()
    {
        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            GCINC(left_value);
            GCINC(right_value);

            auto func = left_value->get_cur_env_func(FUNC_ADD_OP_KEY);
            if (func == nullptr)
            {
                GCFREE(left_value);
                GCFREE(right_value);

                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            GCINC(parameter);

            const auto ret = func->eval(parameter);

            GCFREE(parameter);
            GCFREE(left_value);
            GCFREE(right_value);
            return ret;
        }

        return nullptr;
    }

    GM_Value* GM_AST_SUB_OPERATOR_EXPR::eval()
    {
        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            GCINC(left_value);
            GCINC(right_value);

            auto func = left_value->get_cur_env_func(FUNC_SUB_OP_KEY);
            if (func == nullptr)
            {
                GCFREE(left_value);
                GCFREE(right_value);

                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            GCINC(parameter);

            const auto ret = func->eval(parameter);

            GCFREE(parameter);
            GCFREE(left_value);
            GCFREE(right_value);
            return ret;
        }

        return nullptr;
    }

    GM_Value* GM_AST_MUL_OPERATOR_EXPR::eval()
    {
        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            GCINC(left_value);
            GCINC(right_value);

            auto func = left_value->get_cur_env_func(FUNC_MUL_OP_KEY);
            if (func == nullptr)
            {
                GCFREE(left_value);
                GCFREE(right_value);

                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            GCINC(parameter);

            const auto ret = func->eval(parameter);

            GCFREE(parameter);
            GCFREE(left_value);
            GCFREE(right_value);
            return ret;
        }

        return nullptr;
    }

    GM_Value* GM_AST_DIV_OPERATOR_EXPR::eval()
    {
        auto left_value = get_child(0)->eval();
        auto right_value = get_child(1)->eval();

        if (left_value != nullptr && right_value != nullptr)
        {
            GCINC(left_value);
            GCINC(right_value);

            auto func = left_value->get_cur_env_func(FUNC_DIV_OP_KEY);
            if (func == nullptr)
            {
                GCFREE(left_value);
                GCFREE(right_value);

                PRINT_ERROR_F("FunctionError: %s not found", FUNC_SUB_OP_KEY);
                return nullptr;
            }
            
            auto parameter = GM_GC::alloc_args<GM_Parameter>(get_environment(),
                                                             2, left_value, right_value);
            GCINC(parameter);

            const auto ret = func->eval(parameter);

            GCFREE(parameter);
            GCFREE(left_value);
            GCFREE(right_value);
            return ret;
        }

        return nullptr;
    }

}
