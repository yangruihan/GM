#include "gm_bool_value.hpp"

#include "../../GM.h"

namespace GM
{

    GM_BoolValue::GM_BoolValue(GM_Environment* env,
                               const std::string& token): GM_Value(env)
    {
        if (token == "true")
            m_value = true;
        else if (token == "false")
            m_value = "false";

        _init_functions();
    }

    GM_BoolValue::GM_BoolValue(GM_Environment* env,
                               const bool& value)
                               : GM_Value(env), m_value(value)
    {}
    
    std::string GM_BoolValue::str() const
    {
        return m_value ? "true" : "false";
    }

    void GM_BoolValue::_init_functions()
    {
    }

}