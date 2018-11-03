#include "gm_int_value.hpp"
#include "gm_float_value.hpp"
#include "gm_function.hpp"
#include "gm_list_value.hpp"
#include "../Common/gm_utils.hpp"

#include <sstream>

namespace GM
{

    GM_IntValue::GM_IntValue (std::string& token)
    {
        GM_Utils::get_int_from_str(token, m_value);

        _init_functions();
    }

    GM_IntValue::GM_IntValue(int value): m_value(value)
    {
        _init_functions();
    }

    GM_IntValue::GM_IntValue(double value): m_value(static_cast<int>(value))
    {
        _init_functions();
    }

    GM_IntValue::~GM_IntValue () {}

    void GM_IntValue::_init_functions()
    {
        GM_Value::set_func(GM_Function::create_func(FUNC_ADD_OP_KEY,
                                                    GM_IntValue::__add));
        GM_Value::set_func(GM_Function::create_func(FUNC_SUB_OP_KEY,
                                                    GM_IntValue::__sub));
        GM_Value::set_func(GM_Function::create_func(FUNC_MUL_OP_KEY,
                                                    GM_IntValue::__mul));
        GM_Value::set_func(GM_Function::create_func(FUNC_DIV_OP_KEY,
                                                    GM_IntValue::__div));
    }

    std::string GM_IntValue::str()
    {
        return GM_Utils::format_str("%d", m_value);
    }

    GM_Value* GM_IntValue::__add(const GM_ListValue* args)
    {
        if (args->get_item_count() != 2)
        {
            PRINT_ERROR_F("ArgumentsError: Argument count is not match, need %d, %d given", 2, args->get_item_count());
            return nullptr;
        }

        auto int_arg1 = dynamic_cast<GM_IntValue*>((*args)[0]);
        auto arg2 = (*args)[1];

        auto type2 = arg2->get_type();

        if (GM_TypeUtils::is_number_type(type2))
        {
            if (type2 == T_GM_INT_VALUE)
            {
                auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
                return new GM_IntValue(int_arg1->get_value() + int_arg2->get_value());
            }
            else
            {
                auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
                return new GM_FloatValue(int_arg1->get_value() + float_arg2->get_value());
            }
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_Value* GM_IntValue::__sub(const GM_ListValue* args)
    {
        if (args->get_item_count() != 2)
        {
            PRINT_ERROR_F("ArgumentsError: Argument count is not match, need %d, %d given", 2, args->get_item_count());
            return nullptr;
        }

        auto int_arg1 = dynamic_cast<GM_IntValue*>((*args)[0]);
        auto arg2 = (*args)[1];

        auto type2 = arg2->get_type();

        if (GM_TypeUtils::is_number_type(type2))
        {
            if (type2 == T_GM_INT_VALUE)
            {
                auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
                return new GM_IntValue(int_arg1->get_value() - int_arg2->get_value());
            }
            else
            {
                auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
                return new GM_FloatValue(int_arg1->get_value() - float_arg2->get_value());
            }
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_Value* GM_IntValue::__mul(const GM_ListValue* args)
    {
        if (args->get_item_count() != 2)
        {
            PRINT_ERROR_F("ArgumentsError: Argument count is not match, need %d, %d given", 2, args->get_item_count());
            return nullptr;
        }

        auto int_arg1 = dynamic_cast<GM_IntValue*>((*args)[0]);
        auto arg2 = (*args)[1];

        auto type2 = arg2->get_type();

        if (GM_TypeUtils::is_number_type(type2))
        {
            if (type2 == T_GM_INT_VALUE)
            {
                auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
                return new GM_IntValue(int_arg1->get_value() * int_arg2->get_value());
            }
            else
            {
                auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
                return new GM_FloatValue(int_arg1->get_value() * float_arg2->get_value());
            }
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }

    GM_Value* GM_IntValue::__div(const GM_ListValue* args)
    {
        if (args->get_item_count() != 2)
        {
            PRINT_ERROR_F("ArgumentsError: Argument count is not match, need %d, %d given", 2, args->get_item_count());
            return nullptr;
        }

        auto int_arg1 = dynamic_cast<GM_IntValue*>((*args)[0]);
        auto arg2 = (*args)[1];

        auto type2 = arg2->get_type();

        if (GM_TypeUtils::is_number_type(type2))
        {
            if (type2 == T_GM_INT_VALUE)
            {
                auto int_arg2 = dynamic_cast<GM_IntValue*>(arg2);
                if (int_arg2->get_value() == 0.0)
                {
                    PRINT_ERROR("ZeroDivisionError: integer division or modulo by zero");
                    return nullptr;
                }
                return new GM_IntValue(int_arg1->get_value() / int_arg2->get_value());
            }
            else
            {
                auto float_arg2 = dynamic_cast<GM_FloatValue*>(arg2);
                if (float_arg2->get_value() == 0.0)
                {
                    PRINT_ERROR("ZeroDivisionError: float division or modulo by zero");
                    return nullptr;
                }
                return new GM_FloatValue(int_arg1->get_value() / float_arg2->get_value());
            }
        }

        PRINT_ERROR("TypeError: unsupported operand type(s) for +");
        return nullptr;
    }
}