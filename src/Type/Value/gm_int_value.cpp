#include "gm_int_value.hpp"
#include "../../GM.h"

#include <sstream>

namespace GM
{

    GM_IntValue::GM_IntValue (GM_Environment* env,
                              const std::string& token): GM_NumberValue(env)
    {
        GM_Utils::get_int_from_str(token, m_value);

        _init_functions();
    }

    GM_IntValue::GM_IntValue(GM_Environment* env,
                             int value): GM_NumberValue(env), m_value(value)
    {
        _init_functions();
    }

    GM_IntValue::GM_IntValue(GM_Environment* env,
                             double value): GM_NumberValue(env), m_value(static_cast<int>(value))
    {
        _init_functions();
    }

    GM_IntValue::~GM_IntValue () {}

    void GM_IntValue::_init_functions()
    {
        GM_VALUE_SET_FUNCTION(FUNC_ADD_OP_KEY, 2, GM_IntValue::__add);
        GM_VALUE_SET_FUNCTION(FUNC_SUB_OP_KEY, 2, GM_IntValue::__sub);
        GM_VALUE_SET_FUNCTION(FUNC_MUL_OP_KEY, 2, GM_IntValue::__mul);
        GM_VALUE_SET_FUNCTION(FUNC_DIV_OP_KEY, 2, GM_IntValue::__div);
        GM_VALUE_SET_FUNCTION(FUNC_LS_OP_KEY,  2, GM_IntValue::__ls);
        GM_VALUE_SET_FUNCTION(FUNC_EQ_OP_KEY,  2, GM_IntValue::__eq);
        GM_VALUE_SET_FUNCTION(FUNC_GT_OP_KEY,  2, GM_IntValue::__gt);
        GM_VALUE_SET_FUNCTION(FUNC_LE_OP_KEY,  2, GM_IntValue::__le);
        GM_VALUE_SET_FUNCTION(FUNC_GE_OP_KEY,  2, GM_IntValue::__ge);
        GM_VALUE_SET_FUNCTION(FUNC_NE_OP_KEY,  2, GM_IntValue::__ne);
    }

    std::string GM_IntValue::_str() const
    {
        return GM_Utils::format_str("%d", m_value);
    }

    GM_FUNCTION_I(GM_IntValue, __add)
    {
        auto int_arg1 = param->get_param<GM_IntValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (int_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        auto type2 = arg2->get_type();

        if (type2 == T_GM_INT_VALUE)
        {
            auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
            return GM_Value::int_value(int_arg1->get_environment(),
                                       int_arg1->get_value() + int_arg2->get_value());
        }
        else
        {
            auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
            return GM_Value::float_value(int_arg1->get_environment(),
                                         int_arg1->get_value() + float_arg2->get_value());
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_FUNCTION_I(GM_IntValue, __sub)
    {
        auto int_arg1 = param->get_param<GM_IntValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (int_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        auto type2 = arg2->get_type();
        
        if (type2 == T_GM_INT_VALUE)
        {
            auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
            return GM_Value::int_value(int_arg1->get_environment(),
                                       int_arg1->get_value() - int_arg2->get_value());
        }
        else
        {
            auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
            return GM_Value::float_value(int_arg1->get_environment(),
                                       int_arg1->get_value() - float_arg2->get_value());
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_FUNCTION_I(GM_IntValue, __mul)
    {
        auto int_arg1 = param->get_param<GM_IntValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (int_arg1 == nullptr || arg2 == nullptr)
            return nullptr;
        
        auto type2 = arg2->get_type();
        
        if (type2 == T_GM_INT_VALUE)
        {
            auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
            return GM_Value::int_value(int_arg1->get_environment(),
                                       int_arg1->get_value() * int_arg2->get_value());
        }
        else
        {
            auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
            return GM_Value::float_value(int_arg1->get_environment(),
                                       int_arg1->get_value() * float_arg2->get_value());
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_FUNCTION_I(GM_IntValue, __div)
    {
        auto int_arg1 = param->get_param<GM_IntValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);
        
        if (int_arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        auto type2 = arg2->get_type();
        
        if (type2 == T_GM_INT_VALUE)
        {
            auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
            if (int_arg2->get_value() == 0.0)
            {
                PRINT_ERROR("ZeroDivisionError: integer division or modulo by zero");
                return nullptr;
            }
            return GM_Value::int_value(int_arg1->get_environment(),
                                       int_arg1->get_value() / int_arg2->get_value());
        }
        else
        {
            auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
            if (float_arg2->get_value() == 0.0)
            {
                PRINT_ERROR("ZeroDivisionError: float division or modulo by zero");
                return nullptr;
            }
            return GM_Value::float_value(int_arg1->get_environment(),
                                       int_arg1->get_value() / float_arg2->get_value());
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_FUNCTION_I(GM_IntValue, __ls)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() < arg2->get_value());
    }

    GM_FUNCTION_I(GM_IntValue, __eq)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() == arg2->get_value());
    }

    GM_FUNCTION_I(GM_IntValue, __gt)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() > arg2->get_value());
    }

    GM_FUNCTION_I(GM_IntValue, __le)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() <= arg2->get_value());
    }

    GM_FUNCTION_I(GM_IntValue, __ge)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() >= arg2->get_value());
    }
    
    GM_FUNCTION_I(GM_IntValue, __ne)
    {
        auto arg1 = param->get_param<GM_NumberValue>(0);
        auto arg2 = param->get_param<GM_NumberValue>(1);

        if (arg1 == nullptr || arg2 == nullptr)
            return nullptr;

        return GM_Value::bool_value(param->get_environment(),
                                    arg1->get_value() != arg2->get_value());
    }

}
