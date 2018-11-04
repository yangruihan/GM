#include "gm_value.hpp"
#include "gm_function.hpp"

#include "../GM.h"

namespace GM
{
    
    GM_Function* GM_Value::get_func(std::string func_name) const
    {
        auto it = m_func_dic.find(func_name);
        if (it != m_func_dic.end())
        {
            return it->second;
        }

        return nullptr;
    }

    void GM_Value::set_func(GM_Function* func)
    {
        if (func == nullptr)
        {
            PRINT_ERROR("Nullptr Error: func is nullptr");
            return;
        }

        m_func_dic[func->get_name()] = func;
    }

    /* ----- create value ----- */
    GM_NullValue* GM_Value::null_value()
    { return GM_NullValue::instance; }

    GM_IntValue* GM_Value::int_value (const std::string& token)
    { return new GM_IntValue(token); }

    GM_IntValue* GM_Value::int_value (int value)
    { return new GM_IntValue(value); }

    GM_IntValue* GM_Value::int_value (double value)
    { return new GM_IntValue(value); }

    GM_FloatValue* GM_Value::float_value (const std::string& token)
    { return new GM_FloatValue(token); }

    GM_FloatValue* GM_Value::float_value (int value)
    { return new GM_FloatValue(value); }

    GM_FloatValue* GM_Value::float_value (double value)
    { return new GM_FloatValue(value); }

}
