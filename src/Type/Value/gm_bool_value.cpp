#include "gm_bool_value.hpp"

#include "GM.h"

namespace GM
{

    GM_BoolValue::GM_BoolValue(GM_Environment*& env,
                               const std::string& token): GM_Value(env)
    {
        if (token == "true")
            m_value = true;
        else
            m_value = "false";

        _init_functions();
    }

    GM_BoolValue::GM_BoolValue(GM_Environment*& env,
                               const char* token): GM_Value(env)
    {
        if (strcmp(token, "true") == 0)
            m_value = true;
        else
            m_value = false;

        _init_functions();
    }

    GM_BoolValue::GM_BoolValue(GM_Environment*& env,
                               const bool& value)
                               : GM_Value(env), m_value(value)
    {}
    
    std::string GM_BoolValue::_str() const
    {
        return m_value ? "true" : "false";
    }

    void GM_BoolValue::_init_functions()
    {
    }

}
