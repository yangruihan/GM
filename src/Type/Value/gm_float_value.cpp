#include "gm_float_value.hpp"
#include "../../GM.h"

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
        GM_Value::set_func(GM_Function::create_func(FUNC_ADD_OP_KEY,
                                                    2,
                                                    GM_FloatValue::__add));
        GM_Value::set_func(GM_Function::create_func(FUNC_SUB_OP_KEY,
                                                    2,
                                                    GM_FloatValue::__sub));
        GM_Value::set_func(GM_Function::create_func(FUNC_MUL_OP_KEY,
                                                    2,
                                                    GM_FloatValue::__mul));
        GM_Value::set_func(GM_Function::create_func(FUNC_DIV_OP_KEY,
                                                    2,
                                                    GM_FloatValue::__div));
    }

    std::string GM_FloatValue::str() const
    {
        return GM_Utils::format_str("%lf", m_value);
    }

    GM_Value* GM_FloatValue::__add(const GM_Parameter* param)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() + arg2->get_value());
    }

    GM_Value* GM_FloatValue::__sub(const GM_Parameter* param)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() - arg2->get_value());
    }

    GM_Value* GM_FloatValue::__mul(const GM_Parameter* param)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        return GM_Value::float_value(float_arg1->get_environment(),
                                     float_arg1->get_value() * arg2->get_value());
    }

    GM_Value* GM_FloatValue::__div(const GM_Parameter* param)
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
}
