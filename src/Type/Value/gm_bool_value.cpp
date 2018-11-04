#include "gm_bool_value.hpp"

#include "../../GM.h"

namespace GM
{

    GM_BoolValue::GM_BoolValue(const std::string& token)
    {
        if (token == "true")
            m_value = true;
        else if (token == "false")
            m_value = "false";

        _init_functions();
    }
    
    std::string GM_BoolValue::str() const
    {
        return m_value ? "true" : "false";
    }

    void GM_BoolValue::_init_functions()
    {
    }

}
