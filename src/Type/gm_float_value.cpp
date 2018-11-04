#include "gm_float_value.hpp"
#include "../GM.h"

namespace GM
{

    GM_FloatValue::GM_FloatValue(std::string& token)
    {
        GM_Utils::get_float_from_str(token, m_value);

        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(int value): m_value(value)
    {
        _init_functions();
    }

    GM_FloatValue::GM_FloatValue(double value): m_value(value)
    {
        _init_functions();
    }

    void GM_FloatValue::_init_functions()
    {
        GM_Value::set_func(GM_Function::create_func(FUNC_ADD_OP_KEY,
                                                    GM_FloatValue::__add));
        GM_Value::set_func(GM_Function::create_func(FUNC_SUB_OP_KEY,
                                                    GM_FloatValue::__sub));
        GM_Value::set_func(GM_Function::create_func(FUNC_MUL_OP_KEY,
                                                    GM_FloatValue::__mul));
        GM_Value::set_func(GM_Function::create_func(FUNC_DIV_OP_KEY,
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
        
        return new GM_FloatValue(float_arg1->get_value() + arg2->get_value());
    }

    GM_Value* GM_FloatValue::__sub(const GM_Parameter* param)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        return new GM_FloatValue(float_arg1->get_value() - arg2->get_value());
    }

    GM_Value* GM_FloatValue::__mul(const GM_Parameter* param)
    {
        auto float_arg1 = param->get_param<GM_FloatValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (float_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        return new GM_FloatValue(float_arg1->get_value() * arg2->get_value());
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
        
        return new GM_FloatValue(float_arg1->get_value() / arg2->get_value());
    }
}
