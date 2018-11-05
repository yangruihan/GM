#include "gm_value.hpp"
#include "gm_function.hpp"

#include "../GM.h"

namespace GM
{

    GM_Value::GM_Value(GM_Environment* env): m_environment(env) {}

    GM_Value::~GM_Value() {}

    GM_Function* GM_Value::get_func(std::string func_name) const
    {
        auto func = m_environment->get_var(func_name);
        if (func != nullptr)
        {
            return dynamic_cast<GM_Function*>(func);
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

        m_environment->set_var(func->get_name(), func);
    }

    /* ----- create value ----- */
    GM_NullValue* GM_Value::null_value()
    { return GM_NullValue::instance; }

    GM_BoolValue* GM_Value::bool_value(GM_Environment* env, const std::string &token)
    { return new GM_BoolValue(env, token); }

    GM_BoolValue* GM_Value::bool_value(GM_Environment* env, const bool &value)
    { return new GM_BoolValue(env, value); }

    GM_StrValue* GM_Value::str_value(GM_Environment *env, const std::string &token)
    { return new GM_StrValue(env, token);}

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      const std::string& token)
    { return new GM_IntValue(env, token); }

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      int value)
    { return new GM_IntValue(env, value); }

    GM_IntValue* GM_Value::int_value (GM_Environment* env,
                                      double value)
    { return new GM_IntValue(env, value); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          const std::string& token)
    { return new GM_FloatValue(env, token); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          int value)
    { return new GM_FloatValue(env, value); }

    GM_FloatValue* GM_Value::float_value (GM_Environment* env,
                                          double value)
    { return new GM_FloatValue(env, value); }

}
