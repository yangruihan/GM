#include "gm_float_value.hpp"
#include "GM.h"

namespace GM
{

    GM_FloatValue::GM_FloatValue(GM_Environment* env,
                                 const std::string& token): GM_NumberValue(env)
    {
        GM_Utils::get_float_from_str(token, m_value);

        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(GM_Environment* env,
                                 int value): GM_NumberValue(env), m_value(value)
    {
        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(GM_Environment* env,
                                 double value): GM_NumberValue(env), m_value(value)
    {
        _init_functions();
    }

    void GM_FloatValue::_init_functions()
    {
        GM_VALUE_SET_SELF_FUNCTION(FUNC_ADD_OP_KEY, 2, GM_FloatValue::__add);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_SUB_OP_KEY, 2, GM_FloatValue::__sub);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_MUL_OP_KEY, 2, GM_FloatValue::__mul);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_DIV_OP_KEY, 2, GM_FloatValue::__div);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_LS_OP_KEY,  2, GM_FloatValue::__ls);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_EQ_OP_KEY,  2, GM_FloatValue::__eq);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_GT_OP_KEY,  2, GM_FloatValue::__gt);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_LE_OP_KEY,  2, GM_FloatValue::__le);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_GE_OP_KEY,  2, GM_FloatValue::__ge);
        GM_VALUE_SET_SELF_FUNCTION(FUNC_NE_OP_KEY,  2, GM_FloatValue::__ne);
    }

    std::string GM_FloatValue::_str() const
    {
        return GM_Utils::format_str("%lf", m_value);
    }

    GM_FUNCTION_I(GM_FloatValue, __add)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() + arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __sub)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() - arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __mul)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() * arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __div)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        if (arg2->get_value() == 0.0)
        {
            PRINT_ERROR("ZeroDivisionError: integer division or modulo by zero");
            return nullptr;
        }
        
        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() / arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __ls)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() < arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __eq)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() == arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __gt)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() > arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __le)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() <= arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __ge)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() >= arg2->get_value());
    }

    GM_FUNCTION_I(GM_FloatValue, __ne)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() != arg2->get_value());
    }

}
