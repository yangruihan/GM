#include "gm_var_name_value.hpp"

#include "../../GM.h"

namespace GM
{

    GM_VarNameValue::GM_VarNameValue(GM_Environment* env,
                                     const std::string& var_name)
                                    : GM_Value(env), m_var_name(var_name)
    {}
    
    GM_VarNameValue::~GM_VarNameValue() {}
    
    void GM_VarNameValue::_init_functions() {}

    std::string GM_VarNameValue::str() const
    {
        auto var = get_environment()->get_var(m_var_name);
        if (var == nullptr)
        {
            PRINT_ERROR_F("NameError: name '%s' is not defined", m_var_name.c_str());
            return "";
        }

        auto value = dynamic_cast<GM_Value*>(var);
        if (value != nullptr)
        {
            return value->str();
        }

        auto func = dynamic_cast<GM_Function*>(var);
        if (func != nullptr)
        {
            return func->get_name();
        }

        PRINT_ERROR_F("TypeError: name '%s' variable type is invalid", m_var_name.c_str());
        return "";
    }

}
